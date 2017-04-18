package com.kit.indornavigation.utils;

import android.content.Context;
import android.net.Uri;
import android.os.Environment;
import android.text.format.DateFormat;
import android.util.Log;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.kit.indornavigation.model.LogModel;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Calendar;
import java.util.List;

public final class FileUtils {
    private static final String TAG = FileUtils.class.getSimpleName();
    private static final String nowSession = DateFormat.format("yyyy-MM-dd_hh:mm:ss", Calendar.getInstance().getTime()).toString();

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
}
