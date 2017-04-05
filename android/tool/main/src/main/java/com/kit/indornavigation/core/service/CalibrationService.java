package com.kit.indornavigation.core.service;

import android.app.Service;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.PointF;
import android.os.Binder;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.text.TextUtils;
import android.util.Log;
import android.util.SparseArray;
import android.view.View;
import android.widget.Toast;

import com.davemorrissey.labs.subscaleview.ImageSource;
import com.davemorrissey.labs.subscaleview.ImageViewState;
import com.davemorrissey.labs.subscaleview.SubsamplingScaleImageView;
import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.kit.indornavigation.core.BeaconSearcher;
import com.kit.indornavigation.core.algos.FilteringAlgorithm;
import com.kit.indornavigation.core.algos.MovingAverage;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.BeaconLogModel;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.model.LogModel;
import com.kit.indornavigation.ui.activity.FloorRedactorActivity;
import com.kit.indornavigation.ui.view.IndoorMapRedactor;
import com.kit.indornavigation.utils.FileUtils;

import org.altbeacon.beacon.Beacon;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by user on 04.04.2017.
 */

public class CalibrationService extends Service {

    private static final String TAG = CalibrationService.class.getSimpleName();

    private Thread calibrationThread;

    private final IBinder binder = new CalibrationBindService();
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public class CalibrationBindService extends Binder {

        public CalibrationService getService(){
            return CalibrationService.this;
        }
    }

    @Override
    public void onCreate() {
        super.onCreate();

    }

    public void startCalibration(Runnable task) {
        calibrationThread = new Thread(task);
        calibrationThread.start();
        Log.i(TAG, "calibrationThread started");
    }

    public void pauseCalibration(){
        calibrationThread.interrupt();
    }

    public void stopCalibration(){
        if (calibrationThread == null)
            return;
        calibrationThread.interrupt();
        try {
            calibrationThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        calibrationThread = null;
    }

    public Thread getCalibrationThread() {
        return calibrationThread;
    }
}
