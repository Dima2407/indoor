package com.github.alwayswannasleep.network;

import com.github.alwayswannasleep.network.model.Credentials;
import com.github.alwayswannasleep.network.model.LoginRequest;

import java.util.UUID;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

final class UserManager {

    private final API api;
    private final SharedHelper sharedHelper;
    private final ExecutorService executorService;


    UserManager(API api, SharedHelper sharedHelper) {
        this.api = api;
        this.sharedHelper = sharedHelper;

        executorService = Executors.newSingleThreadExecutor();
    }

    void login(final NetCallback callback) {
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                Credentials credentials = sharedHelper.getCredentials();

                if (credentials == null) {
                    credentials = new Credentials(UUID.randomUUID().toString(), UUID.randomUUID().toString());
                    Credentials result = RetrofitHelper.processCall(api.register(credentials), callback);

                    if (result == null) {
                        return;
                    }

                    sharedHelper.saveCredentials(credentials);
                }

                String token = RetrofitHelper.processCall(api.login(new LoginRequest(credentials.getUsername(), credentials.getPassword())), callback);

                if (token == null) {
                    return;
                }

                sharedHelper.saveToken(token);
                callback.onSuccess();
            }
        });
    }
}
