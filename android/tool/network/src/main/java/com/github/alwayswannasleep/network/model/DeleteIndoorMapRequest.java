package com.github.alwayswannasleep.network.model;

import com.google.gson.annotations.SerializedName;

public final class DeleteIndoorMapRequest {

    @SerializedName("indoorMapId")
    private long id;

    public DeleteIndoorMapRequest(long id) {
        this.id = id;
    }
}
