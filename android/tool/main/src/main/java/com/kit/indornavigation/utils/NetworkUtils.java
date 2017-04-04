package com.kit.indornavigation.utils;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

import com.kit.indornavigation.core.App;
import com.kit.indornavigation.ui.activity.SplashActivity;

/**
 * Created by user on 04.04.2017.
 */

public class NetworkUtils {


    public static boolean isOnline(Context context) {

        ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo netInfo = cm.getActiveNetworkInfo();
        if (netInfo != null && netInfo.isConnectedOrConnecting())
            return true;
        return false;
    }
}
