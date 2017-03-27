package com.kit.indornavigation.utils;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.support.v4.app.ShareCompat;
import android.util.Log;

/**
 * Created by syn on 07.03.17.
 */

public class ShareUtils {

    private static final String TAG = ShareUtils.class.getSimpleName();

    public static void shareFile(Uri uri, Context context) {
        Intent shareIntent = ShareCompat.IntentBuilder.from((Activity) context)
                .setText("Log file")
                .setType("application/txt")
                .setStream(uri)
                .getIntent() ;
        context.startActivity(shareIntent);
    }
}
