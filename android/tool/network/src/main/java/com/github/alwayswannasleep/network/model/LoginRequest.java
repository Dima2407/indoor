package com.github.alwayswannasleep.network.model;

import com.google.gson.annotations.SerializedName;

public final class LoginRequest {
    @SerializedName("username")
    private String username;

    @SerializedName("password")
    private String password;

    public LoginRequest(String username, String password) {
        this.username = username;
        this.password = password;
    }
}
