package com.kit.indornavigation.ui.activity;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.network.Callback;
import com.github.alwayswannasleep.network.NetBridge;
import com.kit.indornavigation.R;
import com.kit.indornavigation.ui.adapter.AbstractRecyclerAdapter;
import com.kit.indornavigation.ui.adapter.FloorsAdapter;
import com.kit.indornavigation.utils.NavigationButtonFactory;

import java.io.File;
import java.util.List;

import butterknife.Bind;

public final class IndoorMapDetailsActivity extends BaseActivity {

    private static final String INDOOR_MAP_KEY = "indoor map key";
    private static final int REQUEST_CODE = 1001;
    private static final String TAG = IndoorMapDetailsActivity.class.getSimpleName();
    private static final int POSITION_IF_SINGLE_FLOOR = 0;

    @Bind(R.id.toolbar)
    Toolbar toolbar;

    @Bind(R.id.floors)
    RecyclerView recyclerView;
    private IndoorMap map;
    private int[] fileDownloadsResult;
    private FloorsAdapter adapter;

    public static void start(Context context, IndoorMap indoorMap) {
        Intent intent = new Intent(context, IndoorMapDetailsActivity.class);
        intent.putExtra(INDOOR_MAP_KEY, indoorMap);

        context.startActivity(intent);
    }

    @Override
    protected void onCreate(@Nullable final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        map = (IndoorMap) getIntent().getSerializableExtra(INDOOR_MAP_KEY);

        toolbar.setNavigationIcon(NavigationButtonFactory.createBackButton(this));
        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                finish();
            }
        });

        toolbar.setTitleTextColor(Color.WHITE);
        toolbar.setTitle(map.getTitle());

        adapter = new FloorsAdapter();

        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(adapter);
        if(map.getFloors().size() == 1){
            downloadFiles(map.getFloors().get(POSITION_IF_SINGLE_FLOOR), POSITION_IF_SINGLE_FLOOR);
            return;
        }
        adapter.setClickListener(new AbstractRecyclerAdapter.OnClickListener<FloorModel>() {
            @Override
            public void onClick(View v, FloorModel item, int position) {
                downloadFiles(item, position);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        app.getNetBridge().loadFloorsByMapId(map.getId(), new Callback() {
            @Override
            protected void onSuccessUi() {
                List<FloorModel> floorModels = getData();
                adapter.setItems(floorModels);
            }

            @Override
            protected void onErrorUi(int code) {
                Toast.makeText(app, "Error loading floors, code: " + code, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void downloadFiles(final FloorModel floorModel, final int floorIndex) {
        fileDownloadsResult = new int[] {-1, -1, -1};

        final Dialog dialog = new AlertDialog.Builder(this)
                .setView(R.layout.dialog_downloading_files)
                .setCancelable(false)
                .show();

        final ProgressBar mapProgress = (ProgressBar) dialog.findViewById(R.id.map_progress);
        final ProgressBar maskProgress = (ProgressBar) dialog.findViewById(R.id.mask_progress);
        final ProgressBar configProgress = (ProgressBar) dialog.findViewById(R.id.config_progress);

        int floorNumber = floorIndex + 1;
        floorModel.setFloorNumber(floorNumber);
        app.getNetBridge().loadMapFile(floorModel, this,
                new NetBridge.ProgressListener() {
                    @Override
                    public void onProgressChanged(byte progress) {
                        mapProgress.setProgress(progress);
                    }
                }, new Callback() {
                    @Override
                    protected void onSuccessUi() {
                        File file = getData();
                        floorModel.setImgPath(file.getAbsolutePath());

                        fileDownloadsResult[0] = 100;

                        onDataLoaded(dialog, floorModel);
                    }

                    @Override
                    protected void onErrorUi(int code) {
                        Toast.makeText(app, "Error loading map - " + code, Toast.LENGTH_SHORT).show();
                        dialog.dismiss();
                    }
                }
        );

        app.getNetBridge().loadMaskFile(floorModel, this,
                new NetBridge.ProgressListener() {
                    @Override
                    public void onProgressChanged(byte progress) {
                        maskProgress.setProgress(progress);
                    }
                }, new Callback() {
                    @Override
                    protected void onSuccessUi() {
                        File file = getData();
                        floorModel.setMaskPath(file.getAbsolutePath());

                        fileDownloadsResult[1] = 100;

                        onDataLoaded(dialog, floorModel);
                    }

                    @Override
                    protected void onErrorUi(int code) {
                        Toast.makeText(app, "Error loading mask - " + code, Toast.LENGTH_SHORT).show();
                        dialog.dismiss();
                    }
                }
        );

        app.getNetBridge().loadConfigFile(floorModel, this,
                new NetBridge.ProgressListener() {
                    @Override
                    public void onProgressChanged(byte progress) {
                        configProgress.setProgress(progress);
                    }
                }, new Callback() {
                    @Override
                    protected void onSuccessUi() {
                        File file = getData();
                        floorModel.setCalibrationFilePath(file.getAbsolutePath());
                        fileDownloadsResult[2] = 100;
                        onDataLoaded(dialog, floorModel);
                    }

                    @Override
                    protected void onErrorUi(int code) {
                        fileDownloadsResult[2] = 0;

                        onDataLoaded(dialog, floorModel);
                    }
                }
        );
    }

    private void onDataLoaded(Dialog dialog, FloorModel floorModel) {
        if (fileDownloadsResult[0] != 100 || fileDownloadsResult[1] != 100 || fileDownloadsResult[2] == -1) {
            return;
        }

        dialog.dismiss();
        FloorRedactorActivity.start(this, map, floorModel, REQUEST_CODE);
        if(map.getFloors().size() == 1){
            this.finish();
        }
    }

    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode != REQUEST_CODE) {
            return;
        }

        if (resultCode != RESULT_OK) {
            return;
        }

        map = (IndoorMap) data.getSerializableExtra(FloorRedactorActivity.MAP_RESULT_EXTRA);
        adapter.setItems(map.getFloors());
    }

    @Override
    public int getLayResId() {
        return R.layout.activity_new_map_creator;
    }
}
