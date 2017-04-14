package khpi.com.demo.net;


import android.content.Context;

import khpi.com.demo.model.Floor;
import khpi.com.demo.net.model.LoginModel;
import khpi.com.demo.utils.FileUtil;
import khpi.com.demo.utils.NetUtil;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MapCacheHelper {

    public static String FOLDER_MAP_DATA = "MapData";
    private static String token = LoginModel.getLoginModel().getToken();
    private static List<String> files = new ArrayList<>();

    private static ExecutorService netExecutor;

    public static void cacheMapData(Context context, final Floor floor, final NetUtil.NetFileListener listener) {
        checkExecutor();

        files.add(floor.getMapPath());
        files.add(floor.getConfigPath());
        files.add(floor.getGraphPath());
        files.add(floor.getMaskPath());

        final Map<String, String> headers = new HashMap<>();
        headers.put("Content-Type", "application/json");
        headers.put("Cache-Control", "no-cache");
        headers.put("Authorization", token);

        File externalFilesDir = context.getExternalFilesDir(FOLDER_MAP_DATA);
        final String baseFolder = externalFilesDir.getAbsolutePath();
        netExecutor.execute(new Runnable() {
            @Override
            public void run() {

                    for (String filename : files) {

                        if(filename==null) continue;
                        File destination = FileUtil.getLocacPath(baseFolder, filename);

                        URL url = FileUtil.getServerPath(
                                "http://185.86.76.206:8081/mob",
                                filename
                        );
                        try {
                            NetUtil.cacheFile(url, destination, headers);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                listener.onSuccess(null);
            }
        });

    }

    private static void checkExecutor() {
        if (netExecutor == null) {
            netExecutor = Executors.newSingleThreadExecutor();
        }
    }

}
