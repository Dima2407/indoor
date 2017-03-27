package com.github.alwayswannasleep.network;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.github.alwayswannasleep.network.model.GenericResponse;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.util.concurrent.Executor;
import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import retrofit2.Call;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

final class RetrofitHelper {
    public static final String DATA_FORMAT = "yyyy-MM-dd'T'HH:mm:ss.SSS";
    private static final String TAG = RetrofitHelper.class.getSimpleName();

    private final API api;

    RetrofitHelper(String url, SharedHelper sharedHelper) {
        Gson gson = new GsonBuilder()
                .setLenient()
                .setDateFormat(DATA_FORMAT)
                .create();

        Retrofit retrofitInstance = new Retrofit.Builder()
                .baseUrl(url)
                .client(new OkHttpClient.Builder()
                        .connectTimeout(10, TimeUnit.SECONDS)
                        .readTimeout(30, TimeUnit.SECONDS)
                        .writeTimeout(30, TimeUnit.SECONDS)
                        .addInterceptor(new AuthenticationInterceptor(sharedHelper))
                        .build()
                )
                .addConverterFactory(GsonConverterFactory.create(
                        gson
                        )
                )
                .callbackExecutor(new Executor() {
                    private final Handler mainHandler = new Handler(Looper.getMainLooper());

                    @Override
                    public void execute(Runnable runnable) {
                        mainHandler.post(runnable);
                    }
                })
                .build();

        api = retrofitInstance.create(API.class);
    }

    API getApi() {
        return api;
    }

    static <T> T processCall(Call<GenericResponse<T>> call, NetCallback callback, boolean invokeSuccess) {
        if (callback != null) {
            callback.putUrl(call.request().url().toString());
        }

        try {
            Response<GenericResponse<T>> response = call.execute();

            Log.d(TAG, "processCall: " + call.request().url().toString());
            Log.d(TAG, "processCall: " + new Gson().toJson(response.body()));
            if (!response.isSuccessful()) {
                if (callback != null) {
                    callback.onError(response.code());
                }

                return null;
            }

            GenericResponse<T> body = response.body();

            if (body.containsError()) {
                if (callback != null) {
                    callback.onError(body.getErrorCode());
                }

                return null;
            }

            if (invokeSuccess && callback != null) {
                callback.onSuccess();
            }

            return body.getData();
        } catch (Exception e) {
            e.printStackTrace();

            if (callback != null) {
                callback.onError(0);
            }
        }

        return null;
    }

    static <T> T processCall(Call<GenericResponse<T>> call, NetCallback callback) {
        return processCall(call, callback, false);
    }
}
