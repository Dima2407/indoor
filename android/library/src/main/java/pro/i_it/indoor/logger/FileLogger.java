package pro.i_it.indoor.logger;

import android.os.Environment;
import android.util.Log;
import org.json.JSONObject;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

class FileLogger {

    private boolean logErrorOnce = true;

    protected final void appendToFile(String name, String data) {
        File f = fileOf(name);

        try (FileWriter fw = new FileWriter(f.getAbsoluteFile(), true);
             BufferedWriter bw = new BufferedWriter(fw)) {
            if (data.endsWith("\n")) {
                bw.write(data);
            } else {
                bw.write(data);
                bw.write("\n");
            }
            bw.flush();
        } catch (IOException e) {
            if (logErrorOnce) {
                Log.w(FileLogger.class.getSimpleName(), "appendToFile: ", e);
                logErrorOnce = false;
            }
        }
    }


    protected final void appendToFile(String name, JSONObject data) {
        File f = fileOf(name);
        boolean firstRecord = !f.exists();

        try (FileWriter fw = new FileWriter(f.getAbsoluteFile(), true);
             BufferedWriter bw = new BufferedWriter(fw)) {
            if (firstRecord) {
                bw.write(data.toString());
            } else {
                bw.write(",");
                bw.write(data.toString());
            }
            bw.flush();
        } catch (IOException e) {
            if(logErrorOnce) {
                Log.w(FileLogger.class.getSimpleName(), "appendToFile: ", e);
                logErrorOnce = false;
            }
        }
    }

    protected final File fileOf(String name) {
        return new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS),
                name);
    }

    protected final void delete(String name){
        new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS),
                name).delete();
    }
}
