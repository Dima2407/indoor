package com.github.alwayswannasleep.network;

import android.content.Context;
import android.util.Log;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.github.alwayswannasleep.models.IndoorMap;
import com.google.gson.Gson;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import okhttp3.ResponseBody;
import retrofit2.Response;

final class MapsManager {

    static final String MAP_TYPE = "map";
    static final String MASK_TYPE = "mask";
    static final String GRAPH_TYPE = "graph";
    static final String CONFIG_TYPE = "config";
    private static final String TAG = MapsManager.class.getSimpleName();

    private final API api;
    private final ExecutorService executorService;

    MapsManager(API api) {
        this.api = api;

        executorService = Executors.newFixedThreadPool(4);
    }

    void loadMaps(final long poiId, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                List<IndoorMap> indoorMaps = RetrofitHelper.processCall(api.getMaps(poiId), callback);

                if (indoorMaps == null) {
                    return;
                }

                callback.putData(indoorMaps);
                callback.onSuccess();
            }
        });
    }

    void loadMap(final long mapId, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                IndoorMap indoorMap = RetrofitHelper.processCall(api.getMap(mapId), callback);

                if (indoorMap == null) {
                    return;
                }

                // TODO: 25.01.2017 save data
                callback.onSuccess();
            }
        });
    }

    void loadFile(final String loadFile, final Context context, final NetBridge.ProgressListener progressListener, final NetCallback callback) {

        executorService.submit(new Runnable() {
            @Override
            public void run() {
                File file;
                try {
                    Log.d(TAG, "run: " + api.loadFile(loadFile).request().url());
                    Response<ResponseBody> response = api.loadFile(loadFile).execute();

                    if (!response.isSuccessful()) {
                        callback.onError(response.code());
                        return;
                    }

                    ResponseBody responseBody = response.body();
                    progressListener.setFileSize(responseBody.contentLength());


                    String fPath = loadFile.substring(1, loadFile.length());

                    final File dir = new File(context.getFilesDir() + "/" + fPath);
                    dir.mkdirs(); //create folders where write files
                    file = new File(dir, fPath.split("/")[fPath.split("/").length - 1]);

                    //  file = new File(context.getCacheDir(), fPath);

                    if (!file.createNewFile() && !file.delete()) {
                        throw new Exception();
                    }

                    file.deleteOnExit();

                    try (OutputStream outputStream = new FileOutputStream(file);
                         InputStream inputStream = responseBody.byteStream()) {
                        byte[] buffer = new byte[40960];

                        while (true) {
                            int readBytesCount = inputStream.read(buffer);

                            if (readBytesCount == -1) {
                                break;
                            }

                            outputStream.write(buffer, 0, readBytesCount);
                            progressListener.onDataDownloaded(readBytesCount);
                        }
                    } catch (IOException e) {
                        throw new Exception(e);
                    }

                    callback.putData(file);
                    callback.onSuccess();
                } catch (Exception e) {
                    e.printStackTrace();

                    callback.onError(0);
                }
            }
        });
    }

    void loadMaps(final Callback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                List<IndoorMap> indoorMaps = RetrofitHelper.processCall(api.getMaps(), callback);

                if (indoorMaps == null) {
                    return;
                }

                callback.putData(indoorMaps);
                callback.onSuccess();
            }
        });
    }

    void updateMap(final IndoorMap map, final FloorModel floorModel, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                map.getFloors().remove(floorModel.getFloorNumber() - 1);
                map.getFloors().add(floorModel.getFloorNumber() - 1, floorModel);
                MultipartBody.Part dataJsonPart = MultipartBody.Part.createFormData("dataJson", "data", RequestBody.create(MediaType.parse("text/plain"), new Gson().toJson(map.getFloors())));

                File configFile = new File(floorModel.getCalibrationFilePath());
                MultipartBody.Part configFilePart = MultipartBody.Part.createFormData("configFile", configFile.getName(), MultipartBody.create(MultipartBody.FORM, configFile));

                IndoorMap indoorMap = RetrofitHelper.processCall(api.updateIndoorMap(map.getId(), configFilePart, dataJsonPart, floorModel.getFloorNumber()), callback);

                if (indoorMap == null) {
                    return;
                }

                callback.putData(indoorMap);
                callback.onSuccess();
            }
        });
    }

    void updateBeaconInFloor(final Long floorId, final List<BeaconModel> beaconModels, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                Object responseBody = RetrofitHelper.processCall(api.updateBeaconByFloor(floorId, beaconModels), callback);

                if (responseBody == null) {
                    return;
                }

                callback.onSuccess();
            }
        });

    }

    void uploadFloorConfig(final FloorModel floorModel, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {

                File configFile = new File(floorModel.getCalibrationFilePath());
                MultipartBody.Part configFilePart = MultipartBody.Part.createFormData("configFile", configFile.getName(), MultipartBody.create(MultipartBody.FORM, configFile));


                Object indoorMap = RetrofitHelper.processCall(api.uploadFloor(floorModel.getId(), configFilePart), callback);

                if (indoorMap == null) {
                    callback.onError(0);
                    return;
                }

                callback.putData(indoorMap);
                callback.onSuccess();

            }
        });

    }

    void loadFloorsByMapId(final long mapId, final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                List<FloorModel> floorModels = RetrofitHelper.processCall(api.loadFloorsByMapId(mapId), callback);

                if (floorModels == null) {
                    return;
                }

                callback.putData(floorModels);
                callback.onSuccess();
            }
        });
    }
}
