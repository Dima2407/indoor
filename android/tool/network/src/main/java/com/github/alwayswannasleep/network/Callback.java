package com.github.alwayswannasleep.network;

import android.os.Handler;
import android.os.Looper;
import android.util.Log;

public abstract class Callback implements NetCallback {

    private String url;
    private Object data;
    private final Handler handler;

    protected Callback() {
        handler = new Handler(Looper.getMainLooper());
    }

    @Override
    public final void onSuccess() {
        Log.i("Callback", "onSuccess: " + url);

        handler.post(new Runnable() {
            @Override
            public void run() {
                onSuccessUi();
            }
        });
    }

    protected abstract void onSuccessUi();

    @Override
    public final void onError(final int code) {
        Log.i("Callback", "onError: " + code + " - " + url);

        handler.post(new Runnable() {
            @Override
            public void run() {
                onErrorUi(code);
            }
        });
    }

    protected abstract void onErrorUi(int code);

    @Override
    public final void putUrl(String url) {
        this.url = url;
    }

    @Override
    public final void putData(Object data) {
        this.data = data;
    }

    @SuppressWarnings("unchecked")
    @Override
    public final <T> T getData() {
        return (T) data;
    }
}
