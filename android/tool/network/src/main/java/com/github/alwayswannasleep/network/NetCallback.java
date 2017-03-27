package com.github.alwayswannasleep.network;

interface NetCallback {

    void onSuccess();

    void onError(int code);

    void putUrl(String url);

    void putData(Object data);

    <T> T getData();
}
