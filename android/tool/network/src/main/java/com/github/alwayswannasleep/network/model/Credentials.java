package com.github.alwayswannasleep.network.model;

import com.google.gson.annotations.SerializedName;

public final class Credentials {

    @SerializedName("username")
    private String username;

    @SerializedName("password")
    private String password;

    public Credentials(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }
}
