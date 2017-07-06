package khpi.com.demo.net;


import android.content.Context;
import android.util.Log;
import khpi.com.demo.model.Floor;
import khpi.com.demo.net.model.LoginModel;
import khpi.com.demo.utils.FileUtil;
import khpi.com.demo.utils.NetUtil;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MapCacheHelper {

    private static final String FOLDER_MAP_DATA = "MapData";
    private final String serverUrl;
    private final ExecutorService netExecutor = Executors.newCachedThreadPool();
    private final String baseFolder;

    public MapCacheHelper(Context context, String serverUrl) {
        File externalFilesDir = context.getExternalFilesDir(FOLDER_MAP_DATA);
        this.baseFolder = externalFilesDir.getAbsolutePath();
        this.serverUrl = serverUrl;
    }

    public void cacheMapData(final Floor floor, final NetUtil.NetFileListener listener) {

        final Map<String, String> headers = new HashMap<>();
        headers.put("Content-Type", "application/json");
        headers.put("Cache-Control", "no-cache");
        headers.put("Authorization", LoginModel.getLoginModel().getToken());



        String serverPath = serverUrl + "mob";
        final CountDownLatch filesWaiter = new CountDownLatch(4);

        netExecutor.submit(new DownloadRunnable(serverPath, baseFolder, floor.getMapPath(), headers, filesWaiter));
        netExecutor.submit(new DownloadRunnable(serverPath, baseFolder, floor.getConfigPath(), headers, filesWaiter));
        netExecutor.submit(new DownloadRunnable(serverPath, baseFolder, floor.getGraphPath(), headers, filesWaiter));
        netExecutor.submit(new DownloadRunnable(serverPath, baseFolder, floor.getMaskPath(), headers, filesWaiter));
        netExecutor.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    filesWaiter.await();
                    listener.onSuccess(null);
                } catch (InterruptedException e) {
                    Log.e(MapCacheHelper.class.getSimpleName(), "run: ", e);
                }
            }
        });

    }


    private static class DownloadRunnable implements Runnable {

        private final String fileUrl;

        private final String baseFolder;

        private final String filename;

        private final Map<String, String> headers;

        private final CountDownLatch waiter;

        DownloadRunnable(String fileUrl, String baseFolder, String filename, Map<String, String> headers, CountDownLatch waiter) {
            this.fileUrl = fileUrl;
            this.baseFolder = baseFolder;
            this.filename = filename;
            this.headers = headers;
            this.waiter = waiter;
        }

        @Override
        public void run() {
            try {
                if(filename != null) {
                    File destination = FileUtil.getLocacPath(baseFolder, filename);

                    URL url = FileUtil.getServerPath(fileUrl, filename);

                    NetUtil.cacheFile(url, destination, headers);
                }
            } catch (IOException e) {
                Log.e(MapCacheHelper.class.getSimpleName(), "run: ", e);
            } finally {
                waiter.countDown();
            }
        }
    }

}
