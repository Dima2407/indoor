package com.github.alwayswannasleep.network.model;

import com.google.gson.annotations.SerializedName;

public final class DeletePoiRequest {

    @SerializedName("poiId")
    private long poiId;

    public DeletePoiRequest(long poiId) {
        this.poiId = poiId;
    }
}
