package com.github.alwayswannasleep.network;

import com.github.alwayswannasleep.models.IndoorPoint;
import com.github.alwayswannasleep.models.Poi;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

final class PointsManager {

    private final API api;
    private final ExecutorService executorService;

    PointsManager(API api) {
        this.api = api;

        executorService = Executors.newSingleThreadExecutor();
    }

    void loadPoints(final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                List<Poi> pois = RetrofitHelper.processCall(api.getPois(), callback);

                if (pois == null) {
                    return;
                }

                callback.putData(pois);
                callback.onSuccess();
            }
        });
    }

    void loadPoi(final long id, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                Poi poi = RetrofitHelper.processCall(api.getPoi(id), callback);

                if (poi == null) {
                    return;
                }

                // TODO: 25.01.2017 save data
                callback.onSuccess();
            }
        });
    }

    void updatePoi(final Poi poi, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                Poi updatedPoi = RetrofitHelper.processCall(api.updatePoi(poi), callback);

                if (updatedPoi == null) {
                    return;
                }

                // TODO: 25.01.2017 save updated data
                callback.onSuccess();
            }
        });
    }

    void loadInpoints(final long mapId, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                List<IndoorPoint> indoorPoints = RetrofitHelper.processCall(api.getIndoorPointsByMapId(mapId), callback);

                if (indoorPoints == null) {
                    return;
                }

                // TODO: 25.01.2017 save data
                callback.onSuccess();
            }
        });
    }

    void loadInpoint(final long id, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                IndoorPoint indoorPoint = RetrofitHelper.processCall(api.getInpoint(id), callback);

                if (indoorPoint == null) {
                    return;
                }

                // TODO: 25.01.2017 save data
                callback.onSuccess();
            }
        });
    }
}
