package com.github.alwayswannasleep.network.util;

public final class UrlBuilder {

    public static String buildGetImageUrl(String baseUrl, String imageName) {
        return baseUrl + "mob/getImage/" + imageName;
    }
}
