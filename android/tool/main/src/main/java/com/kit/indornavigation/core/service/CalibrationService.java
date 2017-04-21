package com.kit.indornavigation.core.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.util.Log;

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
        try {
            calibrationThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
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
