package com.kit.indornavigation.ui.activity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.ActivityInfo;
import android.graphics.PointF;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Parcelable;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.util.Log;
import android.util.SparseArray;
import android.view.GestureDetector;
import android.view.Gravity;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

import com.davemorrissey.labs.subscaleview.ImageSource;
import com.davemorrissey.labs.subscaleview.ImageViewState;
import com.davemorrissey.labs.subscaleview.SubsamplingScaleImageView;
import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.network.Callback;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.kit.indornavigation.R;
import com.kit.indornavigation.core.BeaconSearcher;
import com.kit.indornavigation.core.algos.FilteringAlgorithm;
import com.kit.indornavigation.core.algos.MovingAverage;
import com.kit.indornavigation.core.service.CalibrationService;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.BeaconLogModel;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.model.CalibrationResult;
import com.kit.indornavigation.model.LogModel;
import com.kit.indornavigation.ui.detectors.AddBeaconDetector;
import com.kit.indornavigation.ui.detectors.MoveBeaconDetector;
import com.kit.indornavigation.ui.detectors.RemoveBeaconDetector;
import com.kit.indornavigation.ui.view.IndoorMapRedactor;
import com.kit.indornavigation.utils.FileUtils;
import com.kit.indornavigation.utils.NavigationButtonFactory;
import com.kit.indornavigation.utils.ShareUtils;

import org.altbeacon.beacon.Beacon;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.concurrent.TimeUnit;

public final class FloorRedactorActivity extends BaseActivity {

    public static final String MAP_RESULT_EXTRA = "map result";

    private static final String EXTRA_FLOOR = "extra_floor";
    private static final String PARENT_MAP = "parent map";

    private static final String IMG_STATE = "image view state";
    private static final String IMG_BEACONS = "beacons";
    private static final String ACTIVE_MAP = "active map";
    private static final String INDOOR_MAP = "indoor map";

    private static final int MA_WINDOW = 25;
    private static final String TAG = FloorRedactorActivity.class.getSimpleName();

    private IndoorMapRedactor img;
    private List<GestureDetector> gestureDetectors;

    private CheckBox calibrationBtn;
    private CheckBox startPauseBtn;
    private View startPauseBtnWrapper;
    private TextView timerView;

    private IndoorMap map;
    private FloorModel floorModel;
    private List<CalibrationData> calibrationDatas;
    private List<CalibrationResult> calibrationResults;
    private Toolbar toolbar;
    private MenuItem previousItem;
    private boolean isCalibrating;
    private Handler handler;
    private Runnable timerRunnable;
    private long startTimerTime;

    private Handler uiHandler;
    private Toast noTapPointToast;

    private ServiceConnection serviceConnection;
    private CalibrationService.CalibrationBindService calibrationService;
    private boolean isBound;


    public static void start(
            Activity activity,
            final IndoorMap map,
            final FloorModel floorModelv2,
            int requestCode
    ) {
        Intent intent = new Intent(activity, FloorRedactorActivity.class);
        intent.putExtra(EXTRA_FLOOR, (Parcelable) floorModelv2);
        intent.putExtra(PARENT_MAP, map);

        activity.startActivityForResult(intent, requestCode);
    }

    @SuppressWarnings("ConstantConditions")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        calibrationDatas = new ArrayList<>();
        gestureDetectors = new ArrayList<>();
        handler = new Handler();
        timerRunnable = getTimerRunnable();
        serviceConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                calibrationService = (CalibrationService.CalibrationBindService) service;
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {
                calibrationService = null;
            }
        };

        initViews();
        ImageSource image;

        if (savedInstanceState != null) {
            ImageViewState imgState = (ImageViewState) savedInstanceState.getSerializable(IMG_STATE);
            List<BeaconModel> beacons = savedInstanceState.getParcelableArrayList(IMG_BEACONS);

            Log.i(TAG, "onCreate: " + beacons);

            floorModel = savedInstanceState.getParcelable(ACTIVE_MAP);
            map = (IndoorMap) savedInstanceState.getSerializable(INDOOR_MAP);
            image = ImageSource.uri(floorModel.getImgPath());

            toolbar.setTitle(floorModel.getName());

            img.setImage(image, imgState);
            img.setBeaconModels(beacons, floorModel.getPixelSize());

            img.invalidate();

            if (!TextUtils.isEmpty(floorModel.getCalibrationFilePath())) {
                loadConfigFile();
            } else {
                calibrationResults = new ArrayList<>();
            }

            return;
        }

        map = (IndoorMap) getIntent().getSerializableExtra(PARENT_MAP);
        floorModel = getIntent().getParcelableExtra(EXTRA_FLOOR);
        image = ImageSource.uri(floorModel.getImgPath());

        img.setImage(image);
        img.setBeaconModels(floorModel.getBeacons(), floorModel.getPixelSize());

        img.invalidate();

        img.setOnImageEventListener(new SubsamplingScaleImageView.OnImageEventListener() {
            @Override
            public void onReady() {

            }

            @Override
            public void onImageLoaded() {
                int width = img.getSWidth();
                int height = img.getSHeight();

                if (height > width) {
                    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
                } else {
                    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
                }

                img.setOnImageEventListener(null);
            }

            @Override
            public void onPreviewLoadError(Exception e) {

            }

            @Override
            public void onImageLoadError(Exception e) {

            }

            @Override
            public void onTileLoadError(Exception e) {

            }
        });

        toolbar.setTitle(floorModel.getName());

        if (!TextUtils.isEmpty(floorModel.getCalibrationFilePath())) {
            loadConfigFile();
        } else {
            calibrationResults = new ArrayList<>();
        }
    }

    @Override
    protected void onStart() {
        super.onStart();

        uiHandler = new Handler(Looper.getMainLooper());
    }

    private void loadConfigFile() {
        if (floorModel.getCalibrationFilePath() == null) {
            return;
        }
        Type type = new TypeToken<List<CalibrationResult>>() {
        }.getType();

        try (FileReader reader = new FileReader(floorModel.getCalibrationFilePath())) {
            calibrationResults = new Gson().fromJson(reader, type);
        } catch (Exception e) {
            e.printStackTrace();
            // Calibration file not found; ignore
        } finally {
            if (calibrationResults == null) {
                calibrationResults = new ArrayList<>();
            }

            img.setCalibrationData(calibrationResults);
        }
    }

    @Override
    public int getLayResId() {
        return R.layout.activity_map_redactor;
    }

    @SuppressWarnings("ConstantConditions")
    private void initViews() {

        toolbar = (Toolbar) findViewById(R.id.toolbar);

        toolbar.setNavigationIcon(NavigationButtonFactory.createBackButton(this));
        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();
                intent.putExtra(MAP_RESULT_EXTRA, map);
                setResult(RESULT_OK, intent);
                finish();
            }
        });

        toolbar.inflateMenu(R.menu.menu_floor_redactor);
        toolbar.setOnMenuItemClickListener(new Toolbar.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                if (previousItem != null && item.getGroupId() != R.id.unselected_items) {
                    uncheckPreviousItem(previousItem);
                }

                int itemId = item.getItemId();

                if (previousItem != null && itemId == previousItem.getItemId()) {
                    previousItem = null;
                    return true;
                }

                if (item.getGroupId() != R.id.unselected_items) {
                    previousItem = item;
                }

                switch (itemId) {
                    case R.id.beacon_add_tool:
                        if (item.isChecked()) {
                            uncheckPreviousItem(item);
                            previousItem = null;
                        } else {
                            gestureDetectors.add(new MoveBeaconDetector(img));
                            gestureDetectors.add(new AddBeaconDetector(img));
                            addDetectorsToMap();
                            item.setChecked(true);
                        }
                        break;
                    case R.id.remove_beacons_tool:
                        if (item.isChecked()) {
                            uncheckPreviousItem(item);
                            previousItem = null;
                        } else {
                            gestureDetectors.add(new RemoveBeaconDetector(img));
                            addDetectorsToMap();
                            item.setChecked(true);
                        }
                        break;
                    case R.id.calibration_tool:
                        if (!item.isChecked()) {
                            if (!app.getBeaconSearcher()
                                    .isBluetoothEnabled(FloorRedactorActivity.this)) {
                                Toast.makeText(app, "Please turn on bluetooth.", Toast.LENGTH_SHORT)
                                        .show();
                                return true;
                            }

                            if (img.getBeaconModels().size() < 3) {
                                Toast.makeText(FloorRedactorActivity.this,
                                               "Put at least 3 beacons on map.",
                                               Toast.LENGTH_SHORT
                                ).show();
                                return true;
                            }

                            previousItem = item;
                            img.setCurrentPositionDetector();

                            calibrationBtn.setVisibility(View.VISIBLE);
                            item.setChecked(true);
                            isCalibrating = true;
                        } else {
                            stopCalibration();
                            previousItem = null;
                        }
                        break;

                    case R.id.show_info_window:
                        onInfoBtnPressed();
                        break;

                    case R.id.save_map:
                        onSaveBtnPressed();
                        break;

                    case R.id.share:
                        String filePath = FileUtils.getNowLogFilePath(FloorRedactorActivity.this);
                        File file = new File(filePath);

                        if (file.exists() && file.length() > 0) {
                            ShareUtils.shareFile(Uri.parse("file://" + filePath),
                                                 FloorRedactorActivity.this
                            );
                        } else {
                            Toast.makeText(app,
                                           "Log file is empty. Start calibration for sharing results.",
                                           Toast.LENGTH_SHORT
                            ).show();
                        }
                        break;

                    case R.id.clear_calibration:
                        if (calibrationResults != null) {
                            calibrationResults.clear();
                            img.setCalibrationData(calibrationResults);
                        }
                        FileUtils.saveLog(null, false, getApplicationContext());
                        break;
                }

                return true;
            }
        });

        calibrationBtn = (CheckBox) findViewById(R.id.calibration_state_btn);

        startPauseBtnWrapper = findViewById(R.id.play_pause_btn_wrapper);
        timerView = (TextView) findViewById(R.id.timer_tv);

        startPauseBtn = (CheckBox) findViewById(R.id.play_pause_btn);
        startPauseBtn.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean checked) {
                if (!checked) {
                    pauseCalibration();
                } else {
                    startCalibration();
                }
            }
        });

        calibrationBtn.setOnCheckedChangeListener(new CalibrationStartStopListener());

        img = (IndoorMapRedactor) findViewById(R.id.ma_img);
    }

    private void stopTimer() {
        handler.removeCallbacks(timerRunnable);
        if (uiHandler != null) {
            uiHandler.post(new Runnable() {
                @Override
                public void run() {
                    timerView.setText(null);
                }
            });
        }
    }

    private void startTimer() {
        startTimerTime = System.currentTimeMillis();
        timerRunnable.run();
    }

    public Runnable getTimerRunnable() {
        return new Runnable() {
            @Override
            public void run() {
                if (uiHandler != null) {
                    uiHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            timerView.setText("  " + ((System.currentTimeMillis() - startTimerTime) / 1000) + ":s");
                        }
                    });
                }
                handler.postDelayed(FloorRedactorActivity.this.timerRunnable, 100);
            }
        };
    }

    private void uncheckPreviousItem(MenuItem previousItem) {
        if (previousItem == null) {
            return;
        }

        img.clearDistancePoints();

        removeDetectors();
        gestureDetectors.clear();
        previousItem.setChecked(false);

        if (isCalibrating) {
            stopCalibration();
        }
    }

    private void removeDetectors() {
        for (GestureDetector gestureDetector : gestureDetectors) {
            img.removeGestureDetector(gestureDetector);
        }
    }

    private void addDetectorsToMap() {
        for (GestureDetector gestureDetector : gestureDetectors) {
            img.addGestureDetector(gestureDetector);
        }
    }

    private void onInfoBtnPressed() {
        showInfoDialog();
    }

    private void onSaveBtnPressed() {
        saveData();
    }

    private void saveData() {
        floorModel.setBeacons(img.getBeaconModelsForSaving(floorModel.getPixelSize()));

        for (BeaconModel beaconModel : floorModel.getBeacons()) {
            if (CalibrationResult.listContainsBeacon(calibrationResults, beaconModel)) {
                calibrationResults.get(CalibrationResult.findIndex(calibrationResults, beaconModel))
                        .setCalibratedBeacon(beaconModel);
                }
        }

        saveCalibrationResults();
        if (floorModel.getBeacons() == null || floorModel.getBeacons().size() == 0) {
            Toast.makeText(FloorRedactorActivity.this, "Calibration data null ", Toast.LENGTH_SHORT)
                    .show();
            return;
        }
        app.getNetBridge()
                .updateBeaconInFloor(floorModel.getId(), floorModel.getBeacons(), new Callback() {
                    @Override
                    protected void onSuccessUi() {
                        Toast.makeText(FloorRedactorActivity.this,
                                       R.string.update_beacon_success,
                                       Toast.LENGTH_SHORT
                        ).show();
                    }

                    @Override
                    protected void onErrorUi(int code) {
                        Toast.makeText(FloorRedactorActivity.this,
                                       R.string.fail_update_beacon_success,
                                       Toast.LENGTH_SHORT
                        ).show();
                    }
                });
        app.getNetBridge().uploadFloor(floorModel, new Callback() {
            @Override
            protected void onSuccessUi() {
                Toast.makeText(FloorRedactorActivity.this,
                               R.string.update_floor_config_success,
                               Toast.LENGTH_SHORT
                ).show();
            }

            @Override
            protected void onErrorUi(int code) {
                Toast.makeText(FloorRedactorActivity.this,
                               R.string.fail_update_floor_config_success,
                               Toast.LENGTH_SHORT
                ).show();
            }
        });
    }

    private void saveCalibrationResults() {
        String json = new Gson().toJson(calibrationResults);
        if (TextUtils.isEmpty(json)) {
            return;
        }

        String file = "/" + map.getId() + "_" + floorModel.getFloorNumber() + "_config";
        String filePath = getCacheDir().getAbsolutePath() + file;
        try (FileWriter writer = new FileWriter(filePath)) {
            writer.write(json);
            floorModel.setCalibrationFilePath(filePath);
        } catch (IOException e) {
            e.printStackTrace();
        }

        if (getExternalCacheDir() != null) {
            filePath = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)
                    .getAbsolutePath() + "/" + file + ".json";

            try (FileWriter writer = new FileWriter(filePath)) {
                writer.write(json);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @SuppressLint("DefaultLocale")
    private void showInfoDialog() {
        double width = floorModel.getWidth();
        double height = floorModel.getHeight();

        TextView textView = new TextView(this);
        textView.setGravity(Gravity.CENTER);
        textView.setText(String.format("Building size: %.1f X %.1f", width, height));

        new AlertDialog.Builder(this)
                .setTitle("Building info: ")
                .setPositiveButton("Close", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        dialogInterface.dismiss();
                    }
                })
                .setView(textView)
                .show();
    }

    private void startCalibration() {
        img.clearLastSessionCalibrationResults();
        img.setCalibrationData(calibrationResults);
        img.invalidate();

        bindService(new Intent(this, CalibrationService.class),
                    serviceConnection,
                    Context.BIND_AUTO_CREATE);
        isBound = true;

        if (!img.hasTapPoint()) {
            if (startPauseBtnWrapper.getVisibility() == View.VISIBLE) {
                startPauseBtn.setChecked(false);
            } else {
                calibrationBtn.setChecked(false);
                startPauseBtn.setChecked(false);
            }

            if (noTapPointToast == null) {
                noTapPointToast = Toast.makeText(app,
                                                 "You forget to select your position.",
                                                 Toast.LENGTH_SHORT
                );
            }

            noTapPointToast.show();
            return;
        }

        calibrationBtn.setText("Stop.");
        startPauseBtnWrapper.setVisibility(View.VISIBLE);

        img.removeCurrentPositionDetector();

        final Runnable task = new Runnable() {
            @Override
            public void run() {
                startTimer();

                final long startTime = System.currentTimeMillis();
                final ArrayList<BeaconLogModel> beaconsLog = new ArrayList<>();

                final CalibrationData calibrationData = new CalibrationData();
                PointF tapPoint = img.getTapPoint();
                calibrationData.setPosition(tapPoint);

                final List<BeaconModel> beacons = new ArrayList<>();
                final SparseArray<List<Double>> rssi = new SparseArray<>();
                final SparseArray<List<Double>> txPower = new SparseArray<>();
                final SparseArray<List<Double>> distance = new SparseArray<>();
                final SparseArray<FilteringAlgorithm> algorithms = new SparseArray<>();
                final SparseArray<List<Long>> timestamps = new SparseArray<>();

                BeaconSearcher.BeaconListener beaconListener = new BeaconSearcher.BeaconListener() {
                    @Override
                    public void onBeaconsDetected(
                            Collection<Beacon> stableBeacons,
                            Collection<Beacon> currentBeacons
                    ) {
                        for (Beacon beacon : stableBeacons) {
                            BeaconLogModel logModel = new BeaconLogModel(beacon);

                            BeaconModel beaconOnMap = null;

                            List<BeaconModel> beaconModels = img.getBeaconModels();
                            for (BeaconModel beaconModel : beaconModels) {
                                if (beaconModel.getMacAddress()
                                        .compareTo(beacon.getBluetoothAddress()) == 0) {
                                    beaconOnMap = beaconModel;
                                    break;
                                }
                            }

                            if (beaconOnMap != null) {

                                int hashCode = beaconOnMap.getMacAddress().hashCode();
                                if (!beacons.contains(beaconOnMap)) {
                                    beacons.add(beaconOnMap);
                                }

                                List<Long> timeArray = timestamps.get(hashCode);
                                if (timeArray == null) {
                                    timeArray = new ArrayList<>();
                                    timestamps.put(hashCode, timeArray);
                                }

                                timeArray.add(TimeUnit.MILLISECONDS.toSeconds(System.currentTimeMillis()));

                                FilteringAlgorithm algorithm = algorithms.get(hashCode);

                                if (algorithm == null) {
                                    algorithm = new MovingAverage(MA_WINDOW);
                                    algorithms.put(hashCode, algorithm);
                                }

                                List<Double> list = rssi.get(hashCode);
                                if (list == null) {
                                    list = new ArrayList<>();
                                    rssi.put(hashCode, list);
                                }

                                list.add(algorithm.filter(beacon.getRssi()));

                                list = distance.get(hashCode);
                                if (list == null) {
                                    list = new ArrayList<>();
                                    distance.put(hashCode, list);
                                }

                                PointF position = beaconOnMap.getPosition();
                                PointF calibrationDataPosition = calibrationData.getPosition();

                                double distance = Math.sqrt(Math.pow(position.x - calibrationDataPosition.x,
                                                                     2
                                ) + Math.pow(position.y - calibrationDataPosition.y, 2));
                                list.add(distance * floorModel.getPixelSize());
                            }

                            logModel.setCreateTime(System.currentTimeMillis() - startTime);
                            beaconsLog.add(logModel);
                        }
                    }
                };
                app.getBeaconSearcher().addListener(beaconListener);

                while (!Thread.currentThread().isInterrupted()) {
                }

                List<LogModel> logs = FileUtils.getLogs(FloorRedactorActivity.this);
                if (logs == null) {
                    logs = new ArrayList<>();
                }

                LogModel logModel = new LogModel();
                logModel.setStartTime(startTime);
                logModel.setUserPositionX((float) (tapPoint.x * floorModel.getPixelSize()));
                logModel.setUserPositionY((float) (tapPoint.y * floorModel.getPixelSize()));

                logModel.getBeaconsLog().addAll(beaconsLog);

                logs.add(logModel);
                FileUtils.saveLog(logs, true, FloorRedactorActivity.this);
                app.getBeaconSearcher().removeListener(beaconListener);

                List<BeaconConfigData> configDataList = new ArrayList<>();

                for (BeaconModel beacon : beacons) {
                    BeaconConfigData configData = new BeaconConfigData();
                    int hashcode = beacon.getMacAddress().hashCode();

                    configData.setHash(hashcode);
                    configData.setBeaconModel(beacon);
                    configData.setRssiData(rssi.get(hashcode));
                    configData.setTxData(txPower.get(hashcode));
                    configData.setDistanceData(distance.get(hashcode));
                    configData.setTimestampsData(timestamps.get(hashcode));

                    configDataList.add(configData);
                }

                calibrationData.setConfigDatas(configDataList);

                calibrationDatas.add(calibrationData);

                stopTimer();
            }
        };

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                calibrationService.getService().startCalibration(task);
            }
        }).start();
    }

    private void pauseCalibration() {
        calibrationService.getService().pauseCalibration();
        img.removeTapPoint();

        if (startPauseBtnWrapper.getVisibility() != View.VISIBLE) {
            return;
        }

        img.setCurrentPositionDetector();

        List<CalibrationResult> copyResults = new ArrayList<>();
        for (int i = 0; i < calibrationResults.size(); i++) {
            copyResults.add(calibrationResults.get(i).clone());
        }

        List<CalibrationResult> newCalibrationResults = app.getAlgoManager()
                .calibrateBeacons(img.getBeaconModels(),
                                  copyResults,
                                  calibrationDatas,
                                  floorModel);

        List<CalibrationResult> tmp = new ArrayList<>(newCalibrationResults);

        for (int i = 0; i < tmp.size(); i++) {
            if (!calibrationResults.contains(tmp.get(i))) {
                continue;
            }

            if (calibrationResults.get(calibrationResults.indexOf(tmp.get(i)))
                    .getResults()
                    .size() == tmp.get(i).getResults().size()) {
                tmp.remove(i--);
            }
        }

        img.setLastSessionCalibrationResults(tmp);
        calibrationResults = newCalibrationResults;
        calibrationDatas.clear();

        Toast.makeText(this, "Please choose your real position on map.", Toast.LENGTH_SHORT).show();
    }

    private void stopCalibration() {
        if (!isCalibrating) {
            return;
        }

        isCalibrating = false;
        uncheckPreviousItem(previousItem);

        startPauseBtn.setChecked(false);

        calibrationBtn.setVisibility(View.INVISIBLE);
        startPauseBtnWrapper.setVisibility(View.INVISIBLE);

        img.removeTapPoint();
        img.removeCurrentPositionDetector();

        calibrationBtn.setText("Start.");
        calibrationBtn.setChecked(false);

        if (isBound) {
            calibrationService.getService().stopCalibration();
            unbindService(serviceConnection);
            isBound = false;
        }

        stopTimer();

        img.clearLastSessionCalibrationResults();
        img.setCalibrationData(calibrationResults);
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        List<BeaconModel> beacons = img.getBeaconModels();
        Log.i(TAG, "onSaveInstanceState: " + beacons);
        Log.i(TAG, "onSaveInstanceState: " + floorModel.getPixelSize());

        List<BeaconModel> result = new ArrayList<>();

        for (int i = 0; i < beacons.size(); i++) {
            BeaconModel model = beacons.get(i);
            BeaconModel beaconModel = new BeaconModel(model);
            beaconModel.setPosition(new PointF(((float) (model.getPosition().x * floorModel.getPixelSize())),
                                               (float) (model.getPosition().y * floorModel.getPixelSize())
            ));
            beaconModel.setPositionZ(model.getPositionZ());

            result.add(i, beaconModel);
        }

        Log.i(TAG, "onSaveInstanceState: " + beacons);

        outState.putSerializable(IMG_STATE, img.getState());
        outState.putParcelableArrayList(IMG_BEACONS, (ArrayList<BeaconModel>) result);
        outState.putParcelable(ACTIVE_MAP, floorModel);
        outState.putSerializable(INDOOR_MAP, map);
    }

    @Override
    public void onBackPressed() {
        setResult(RESULT_CANCELED);
        super.onBackPressed();
    }

    @Override
    protected void onStop() {
        super.onStop();

        uiHandler = null;
    }

    private class CalibrationStartStopListener implements CompoundButton.OnCheckedChangeListener {

        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
            if (isChecked) {
                startPauseBtn.setChecked(true);
            } else {
                stopCalibration();
                previousItem = null;
            }
        }
    }
}
