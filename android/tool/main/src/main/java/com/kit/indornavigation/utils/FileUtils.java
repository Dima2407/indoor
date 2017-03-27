package com.kit.indornavigation.utils;

import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PointF;
import android.net.Uri;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Environment;
import android.text.format.DateFormat;
import android.util.Log;
import android.util.SparseArray;
import android.widget.Toast;

import com.github.alwayswannasleep.models.FloorModel;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.model.LogModel;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URI;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

public final class FileUtils {
    private static final String DIR = "IndoorNavigation";
    private static final String IMAGE_NAME = "IndoorMap";
    private static final String TAG = FileUtils.class.getSimpleName();
    private static final String nowSession = DateFormat.format("yyyy-MM-dd_hh:mm:ss", Calendar.getInstance().getTime()).toString();

    public static String copyFile(Intent data, Context context) {
        if (data.getData().toString().contains("file:/")) {
            return data.getData().toString();
        }

        File result = createImageFile(context);
        InputStream inputStream = null;
        OutputStream outputStream = null;
        try {
            inputStream = context.getContentResolver().openInputStream(data.getData());
            outputStream = new FileOutputStream(result);

            byte[] buffer = new byte[1024];

            int length;
            while ((length = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, length);
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (inputStream != null) {
                    inputStream.close();
                }

                if (outputStream != null) {
                    outputStream.flush();
                    outputStream.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return Uri.fromFile(result).toString();
    }

    private static File createImageFile(Context context) {
        File dir = context.getExternalFilesDir(DIR);
        File jpg = null;
        try {
            jpg = File.createTempFile(
                    IMAGE_NAME,
                    ".jpg",
                    dir
            );
        } catch (IOException e) {
            e.printStackTrace();
        }

        return jpg;
    }

    public static String getDataDirectiry(Context context) {
        PackageManager m = context.getPackageManager();
        String s = context.getPackageName();
        PackageInfo p = null;
        try {
            p = m.getPackageInfo(s, 0);
            s = p.applicationInfo.dataDir;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return s;
    }

    public static void getMapPhotoDirectory(Context context) {

    }

    public static int loadTexture(final Context context, final int resourceId) {
        final int[] textureHandle = new int[1];

        GLES20.glGenTextures(1, textureHandle, 0);

        if (textureHandle[0] != 0) {
            final BitmapFactory.Options options = new BitmapFactory.Options();
            options.inScaled = false;

            final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resourceId, options);

            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureHandle[0]);

            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);

            GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);

            bitmap.recycle();
        }

        if (textureHandle[0] == 0) {
            throw new RuntimeException("Error loading texture.");
        }

        return textureHandle[0];
    }

    public static String saveCalibrationData(CalibrationData calibrationData, FloorModel floorModel, Context context) {
        File filesDir = context.getExternalFilesDir(null);
        if (filesDir == null) {
            Toast.makeText(context, "Can't save configuration file. External storage may be unavailable.", Toast.LENGTH_SHORT).show();
            return null;
        }

        String fileName = floorModel.getName() + "_" + floorModel.getMapUid() + ".ini";
        File file = new File(filesDir, fileName);

        FileWriter fileWriter = null;
        try {
            if (file.exists() && !file.delete()) {
                Toast.makeText(context, "There is some problems while creating configuration file.", Toast.LENGTH_SHORT).show();
                return null;
            }

            if (!file.createNewFile()) {
                Toast.makeText(context, "There is some problems while creating configuration file.", Toast.LENGTH_SHORT).show();
                return null;
            }

            fileWriter = new FileWriter(file);

            List<BeaconConfigData> configDatas = calibrationData.getConfigDatas();
            for (BeaconConfigData configData : configDatas) {
                for (int i = 0; i < configData.getRssiData().size(); i++) {
                    String fileNext =
                            configData.getHash() + "," +
                                    +configData.getRssiData().get(i) + "," +
                                    +configData.getDistanceData().get(i) + "," +
                                    +calibrationData.getPosition().x + "," +
                                    +calibrationData.getPosition().y + ",";

                    if (configData.getTxData() != null) {
                        fileNext += configData.getTxData().get(i) + "," +
                                +configData.getDamp().get(i);
                    }

                    fileNext += "\n";

                    fileWriter.write(fileNext);
                }
            }

            return Uri.fromFile(file).toString();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fileWriter != null) {
                try {
                    fileWriter.flush();
                    fileWriter.close();
                } catch (IOException e) {
                    try {
                        fileWriter.flush();
                        fileWriter.close();
                    } catch (IOException e1) {
                        e.printStackTrace();
                    }
                }
            }
        }

        return null;
    }

    public static String getNowLogFilePath(Context context) {
        return Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getPath() + "/" + "Logs_" + nowSession + ".json";
    }

    public static <T> String saveLog(T logObject, boolean append, Context context) {
        File filesDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
        if (filesDir == null) {
            Toast.makeText(context, "Can't save configuration file. External storage may be unavailable.", Toast.LENGTH_SHORT).show();
            return null;
        }

        String fileName = "Logs_" + nowSession + ".json";
        File file = new File(filesDir, fileName);

        FileWriter fileWriter = null;
        try {
            if (file.exists() && !file.delete()) {
                Toast.makeText(context, "There is some problems while creating configuration file.", Toast.LENGTH_SHORT).show();
                return null;
            }

            if (!file.createNewFile()) {
                Toast.makeText(context, "There is some problems while creating configuration file.", Toast.LENGTH_SHORT).show();
                return null;
            }

            String str;
            if (logObject == null) {
                str = "";
            } else {
                str = new Gson().toJson(logObject);
            }

            fileWriter = new FileWriter(file, append);
            fileWriter.write(str);

            Log.d(TAG, "saveLog: ");
            return Uri.fromFile(file).toString();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fileWriter != null) {
                try {
                    fileWriter.flush();
                    fileWriter.close();
                } catch (IOException e) {
                    try {
                        fileWriter.flush();
                        fileWriter.close();
                    } catch (IOException e1) {
                        e.printStackTrace();
                    }
                }
            }
        }
        return null;
    }

    public static List<LogModel> getLogs(Context context) {
        File filesDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
        String fileName = "Logs_" + nowSession + ".json";
        File file = new File(filesDir, fileName);

        if (!file.exists()) {
            return null;
        }

        try {
            FileReader fileReader = new FileReader(file);
            StringBuilder builder = new StringBuilder();
            char[] buffer = new char[256];
            int count;

            while ((count = fileReader.read(buffer)) != -1) {
                builder.append(buffer, 0, count);
            }

            List<LogModel> logs = new Gson().fromJson(builder.toString(), new TypeToken<List<LogModel>>() {
            }.getType());
            Log.d(TAG, "getLogFileByClass: ");
            Log.d(TAG, builder.toString());
            return logs;
        } catch (IOException e) {
            Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }

        return null;
    }

    public static CalibrationData readCalibrationData(String filePath) {
        CalibrationData calibrationData = new CalibrationData();
        File file = new File(URI.create(filePath));

        if (!file.exists()) {
            return null;
        }

        try {
            FileReader fileReader = new FileReader(file);
            StringBuilder builder = new StringBuilder();
            char[] buffer = new char[256];
            int count;

            while ((count = fileReader.read(buffer)) != -1) {
                builder.append(buffer, 0, count);
            }

            String[] strings = builder.toString().split("\n");
            List<BeaconConfigData> beaconConfigDatas = new ArrayList<>();

            final List<Integer> beacons = new ArrayList<>();
            final SparseArray<List<Double>> rssi = new SparseArray<>();
            final SparseArray<List<Double>> txPower = new SparseArray<>();
            final SparseArray<List<Double>> distance = new SparseArray<>();
            final SparseArray<List<Double>> damp = new SparseArray<>();

            for (String string : strings) {
                if (string.isEmpty()) {
                    continue;
                }

                String[] split = string.split(",");

                int hashCode = Integer.parseInt(split[0]);
                if (!beacons.contains(hashCode)) {
                    beacons.add(hashCode);
                }

                List<Double> list = rssi.get(hashCode);
                if (list == null) {
                    list = new ArrayList<>();
                    rssi.put(hashCode, list);
                }

                list.add(Double.parseDouble(split[1]));

                list = distance.get(hashCode);
                if (list == null) {
                    list = new ArrayList<>();
                    distance.put(hashCode, list);
                }

                list.add(Double.parseDouble(split[2]));

                if (calibrationData.getPosition() == null) {
                    calibrationData.setPosition(new PointF(Double.valueOf(split[3]).floatValue(), Double.valueOf(split[4]).floatValue()));
                }

                if (split.length == 5) {
                    continue;
                }

                list = txPower.get(hashCode);
                if (list == null) {
                    list = new ArrayList<>();
                    txPower.put(hashCode, list);
                }

                list.add(Double.parseDouble(split[5]));

                list = damp.get(hashCode);
                if (list == null) {
                    list = new ArrayList<>();
                    damp.put(hashCode, list);
                }

                list.add(Double.parseDouble(split[6]));
            }

            for (Integer beacon : beacons) {
                BeaconConfigData configData = new BeaconConfigData();
                configData.setHash(beacon);
                configData.setRssiData(rssi.get(beacon));
                configData.setDistanceData(distance.get(beacon));

                beaconConfigDatas.add(configData);
            }

            calibrationData.setConfigDatas(beaconConfigDatas);
            return calibrationData;
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }
}
