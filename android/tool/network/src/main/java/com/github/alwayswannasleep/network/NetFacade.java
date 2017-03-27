package com.github.alwayswannasleep.network;

import android.content.Context;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.models.Poi;

import java.util.List;

import okhttp3.Interceptor;

public final class NetFacade implements NetBridge {

    private final MapsManager mapsManager;
    private final PointsManager pointsManager;
    private final UserManager userManager;
    private final SharedHelper sharedHelper;

    public static NetBridge instantiate(String url, Context context) {
        return new NetFacade(url, context);
    }

    private NetFacade(String url, Context context) {
        sharedHelper = new SharedHelper(context);
        RetrofitHelper retrofitHelper = new RetrofitHelper(url, sharedHelper);
        API api = retrofitHelper.getApi();

        mapsManager = new MapsManager(api);
        pointsManager = new PointsManager(api);
        userManager = new UserManager(api, sharedHelper);
    }

    @Override
    public Interceptor getAuthInterceptor() {
        return new AuthenticationInterceptor(sharedHelper);
    }

    @Override
    public void loadPois(NetCallback callback) {
        pointsManager.loadPoints(callback);
    }

    @Override
    public void loadPoi(long id, NetCallback callback) {
        pointsManager.loadPoi(id, callback);
    }

    @Override
    public void updatePoi(Poi poi, NetCallback callback) {
        pointsManager.updatePoi(poi, callback);
    }

    @Override
    public void loadMaps(long poiId, NetCallback callback) {
        mapsManager.loadMaps(poiId, callback);
    }

    @Override
    public void loadMap(long mapId, NetCallback callback) {
        mapsManager.loadMap(mapId, callback);
    }

    @Override
    public void updateMap(IndoorMap map, FloorModel floorModel, NetCallback callback) {
        mapsManager.updateMap(map, floorModel, callback);
    }

    @Override
    public void updateBeaconInFloor(long floorId, List<BeaconModel> beaconModels, final NetCallback callback) {
        mapsManager.updateBeaconInFloor(floorId, beaconModels, callback);
    }

    @Override
    public void uploadFloor(FloorModel floorModel, NetCallback callback) {
        mapsManager.uploadFloorConfig(floorModel, callback);
    }


    @Override
    public void getInpoints(long mapId, NetCallback callback) {
        pointsManager.loadInpoints(mapId, callback);
    }

    @Override
    public void getInpoint(long id, NetCallback callback) {
        pointsManager.loadInpoint(id, callback);
    }

    @Override
    public void login(NetCallback callback) {
        userManager.login(callback);
    }

    @Override
    public void loadMapFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback) {
        mapsManager.loadFile(floorModel.getMapPath(), context, progressListener, callback);
    }

    @Override
    public void loadMaskFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback) {
        mapsManager.loadFile(floorModel.getMaskPath(), context, progressListener, callback);
    }

    @Override
    public void loadGraphFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback) {
        mapsManager.loadFile(floorModel.getGraphPath(), context, progressListener, callback);
    }

    @Override
    public void loadConfigFile(FloorModel floorModel, Context context, ProgressListener progressListener, NetCallback callback) {
        mapsManager.loadFile(floorModel.getConfigPath(), context, progressListener, callback);
    }

    @Override
    public void loadMaps(final Callback callback) {
        mapsManager.loadMaps(callback);
    }

    @Override
    public void loadFloorsByMapId(long mapId, NetCallback callback) {
        mapsManager.loadFloorsByMapId(mapId, callback);
    }
}
