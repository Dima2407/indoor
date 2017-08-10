package khpi.com.demo.utils;

import android.content.Context;

import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by kit on 9/25/16.
 */

public class FileUtil {

    public static boolean createIfNotExist(File destination) {
        if (!destination.exists()) {
            if (!destination.getParentFile().exists()) {
                destination.getParentFile().mkdirs();
            }
            try {
                destination.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
                return false;
            }
        }
        return true;
    }

    public static File getLocacPath(Context context, String mapId, String floorId, String filename){
        return new File(context.getExternalFilesDir("MapData")+"/"+mapId+"/"+floorId+"/"+filename+".jpg");
    }

    public static File getLocacPath(Context context, String url){
        return new File(context.getExternalFilesDir("MapData"), url + ".jpg");
    }

    public static File getLocacPath(String baseFolder, String mapId, String floorId, String filename){
        return new File(baseFolder+"/"+mapId+"/"+floorId+"/"+filename+".jpg");
    }

    public static File getLocacPath(String baseFolder, String url){
        return new File(baseFolder+ url+".jpg");
    }

    public static URL getServerPath(String serverUrl, String mapId, String floorId, String filename){
        try {
            return new URL(serverUrl+"/"+mapId+"/"+floorId+"/"+filename);
        } catch (MalformedURLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static URL getServerPath(String serverUrl, String url){
        try {
            return new URL(serverUrl + url);
        } catch (MalformedURLException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static boolean deleteFile(File file) {
        boolean deletedAll = true;
        if (file != null) {
            if (file.isDirectory()) {
                String[] children = file.list();
                for (int i = 0; i < children.length; i++) {
                    deletedAll = deleteFile(new File(file, children[i])) && deletedAll;
                }
            } else {
                deletedAll = file.delete();
            }
        }

        return deletedAll;
    }

}
