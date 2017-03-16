package khpi.com.demo.net;

import android.os.Handler;
import android.os.Looper;
import android.support.annotation.NonNull;

import khpi.com.demo.GsonWrapper;

import java.util.concurrent.Executor;
import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

final class RetrofitHelper {

    private API api;

    RetrofitHelper(String url) {

        Retrofit.Builder builder = new Retrofit.Builder();
        builder.baseUrl(url);
        builder.addConverterFactory(GsonConverterFactory.create(GsonWrapper.getGson()));
        builder.callbackExecutor(new Executor() {
            final Handler handler = new Handler(Looper.getMainLooper());

            @Override
            public void execute(@NonNull Runnable runnable) {
                handler.post(runnable);
            }
        });
        builder.client(getClient());
        builder.validateEagerly(true);
        builder.build();
        api = builder.build().create(API.class);
    }

    @NonNull
    private OkHttpClient getClient() {
        HttpLoggingInterceptor interceptor = new HttpLoggingInterceptor();
        interceptor.setLevel(HttpLoggingInterceptor.Level.BODY);
        return new OkHttpClient.Builder()
                .connectTimeout(30, TimeUnit.SECONDS)
                .writeTimeout(30, TimeUnit.SECONDS)
                .readTimeout(30, TimeUnit.SECONDS)
                .addInterceptor(interceptor)
                .build();
    }

    API getApi() {
        return api;
    }
}
