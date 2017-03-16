package khpi.com.demo.utils;

import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import java.io.Closeable;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.Map;

public class NetUtil {

    private static final int READ_TIMEOUT = 30*1000;

    public static boolean cacheFile(@NonNull URL url,
                                    @NonNull File destination) throws IOException {
        return cacheFile(url,destination,null,null);
    }

    public static boolean cacheFile(@NonNull URL url,
                                    @NonNull File destination,
                                    @Nullable Map<String, String> headers) throws IOException {
        return cacheFile(url,destination,headers,null);
    }

    public static boolean cacheFile(@NonNull URL url,
                                    @NonNull File destination,
                                    @Nullable Map<String, String> headers,
                                    @Nullable NetProgressListener netFileListener) throws IOException {
        if(destination.exists()){
            return true;
        }

        Log.d("NetUtil", "Start cache:" + url);
        URLConnection connection = url.openConnection();
        connection.setDoInput(true);
        connection.setReadTimeout(READ_TIMEOUT);
        if (headers != null) {
            for (Map.Entry<String, String> header : headers.entrySet()) {
                connection.setRequestProperty(header.getKey(), header.getValue());
            }
        }
        try {
            connection.connect();
        }catch (FileNotFoundException e){
            return false;
        }

        int total = connection.getContentLength();
        int done = 0;

        InputStream in = connection.getInputStream();
        if (!FileUtil.createIfNotExist(destination)) {
            return false;
        }
        OutputStream out = new FileOutputStream(destination);
        byte[] data = new byte[1024];
        int count = 0;
        while ((count = in.read(data)) != -1) {
            done += count;
            out.write(data, 0, count);
            if (netFileListener != null) netFileListener.onProgress(done, total);
        }

        out.flush();
        closeQuietly(out);
        closeQuietly(in);
        Log.d("NetUtil", "End cache:" + url);
        return true;
    }

    private static void closeQuietly(Closeable c) {
        try {
            c.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public interface NetFileListener extends NetProgressListener {
        void onError(Throwable throwable);

        void onSuccess(File result);

    }

    public interface NetProgressListener {

        void onProgress(int done, int total);
    }

    private class SimpleNetFileListener implements NetFileListener {

        private NetFileListener listener;
        private Handler handler;

        public SimpleNetFileListener(NetFileListener listener, Handler handler) {
            this.listener = listener;
            this.handler = handler;
        }

        @Override
        public void onError(final Throwable throwable) {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    listener.onError(throwable);
                }
            });
        }

        @Override
        public void onSuccess(final File result) {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    listener.onSuccess(result);
                }
            });
        }

        @Override
        public void onProgress(final int done, final int total) {
            handler.post(new Runnable() {
                @Override
                public void run() {
                    listener.onProgress(done, total);
                }
            });
        }
    }
}
