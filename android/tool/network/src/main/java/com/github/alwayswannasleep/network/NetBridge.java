package com.github.alwayswannasleep.network;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.models.Poi;

import java.util.List;

import okhttp3.Interceptor;

public interface NetBridge {

    void loadPois(NetCallback callback);

    void loadPoi(long id, NetCallback callback);

    void updatePoi(Poi poi, NetCallback callback);

    void loadMaps(long poiId, NetCallback callback);

    void loadMap(long mapId, NetCallback callback);

    void getInpoints(long mapId, NetCallback callback);

    void getInpoint(long id, NetCallback callback);

    void login(NetCallback callback);

    Interceptor getAuthInterceptor();

    void loadMapFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback);

    void loadMaskFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback);

    void loadGraphFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback);

    void loadConfigFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback);

    void loadMaps(Callback callback);

    void updateMap(IndoorMap map, FloorModel floorModel, NetCallback callback);

    void updateBeaconInFloor(long floorId, List<BeaconModel> beaconModels, final NetCallback callback);

    void uploadFloor(final FloorModel floorModel, final NetCallback callback);

    void loadFloorsByMapId(final long mapId, final NetCallback callback);

    abstract class ProgressListener {
        private final Handler handler;

        private long percentageFrame;
        private byte previousProgress;
        private long downloadedData;

        protected ProgressListener() {
            handler = new Handler(Looper.getMainLooper());
        }

        final void setFileSize(long fileSize) {
            percentageFrame = fileSize / 100;
        }

        final void onDataDownloaded(long downloadedSizeCount) {
            downloadedData += downloadedSizeCount;
            final byte percent = (byte) (downloadedData / percentageFrame);

            if (percent == previousProgress) {
                return;
            }

            previousProgress = percent;
            handler.post(new Runnable() {
                @Override
                public void run() {
                    onProgressChanged(percent);
                }
            });
        }

        public abstract void onProgressChanged(byte progress);
    }
}
