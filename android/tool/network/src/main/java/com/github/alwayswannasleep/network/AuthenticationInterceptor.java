package com.github.alwayswannasleep.network;

import android.text.TextUtils;

import java.io.IOException;

import okhttp3.Interceptor;
import okhttp3.Request;
import okhttp3.Response;


final class AuthenticationInterceptor implements Interceptor {

    private final SharedHelper sharedHelper;

    AuthenticationInterceptor(SharedHelper sharedHelper) {
        this.sharedHelper = sharedHelper;
    }

    @Override
    public Response intercept(Chain chain) throws IOException {
        Request request = chain.request();
        Request.Builder builder = request.newBuilder();

        String token = sharedHelper.getToken();
        if (!TextUtils.isEmpty(token)) {
            builder.addHeader("Authorization", token);
        }

        return chain.proceed(builder.build());
    }
}
