package com.github.alwayswannasleep.network;

import android.content.Context;
import android.content.SharedPreferences;

import com.github.alwayswannasleep.network.model.Credentials;

final class SharedHelper {

    private static final String SHARED_NAME = "indoor-tool";
    private static final String TOKEN = "token";
    private static final String USERNAME = "username";
    private static final String PASSWORD = "password";

    private final SharedPreferences sharedPreferences;

    SharedHelper(final Context context) {
        sharedPreferences = context.getSharedPreferences(SHARED_NAME, Context.MODE_PRIVATE);
    }

    Credentials getCredentials() {
        if (sharedPreferences.contains(USERNAME) && sharedPreferences.contains(PASSWORD)) {
            return new Credentials(sharedPreferences.getString(USERNAME, null), sharedPreferences.getString(PASSWORD, null));
        }

        return null;
    }

    void saveCredentials(Credentials credentials) {
        sharedPreferences.edit().putString(USERNAME, credentials.getUsername()).putString(PASSWORD, credentials.getPassword()).apply();
    }

    String getToken() {
        return sharedPreferences.getString(TOKEN, null);
    }

    void saveToken(String token) {
        sharedPreferences.edit().putString(TOKEN, token).apply();
    }
}
