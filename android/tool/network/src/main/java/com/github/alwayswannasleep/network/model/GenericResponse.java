package com.github.alwayswannasleep.network.model;

import com.google.gson.annotations.SerializedName;

public final class GenericResponse<T> {

    @SerializedName("data")
    private T data;

    @SerializedName("error")
    private Error error;

    @SerializedName("message")
    private String message;

    public T getData() {
        return data;
    }

    public int getErrorCode() {
        return error.code;
    }

    public boolean containsError() {
        return error != null;
    }

    public String getMessage() {
        return message;
    }

    private static final class Error {

        @SerializedName("code")
        private int code;
    }
}
