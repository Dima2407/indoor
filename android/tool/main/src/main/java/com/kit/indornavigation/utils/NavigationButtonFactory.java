package com.kit.indornavigation.utils;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.support.annotation.NonNull;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;

public final class NavigationButtonFactory {

    private static final int BACK_STATE = 1;
    private static final int HAMBURGER_STATE = 0;

    private NavigationButtonFactory() {
    }

    public static Drawable createBackButton(Context context) {
        return generateDrawable(context, BACK_STATE);
    }

    public static Drawable createHamburgerButton(Context context) {
        return generateDrawable(context, HAMBURGER_STATE);
    }

    @NonNull
    private static Drawable generateDrawable(final Context context, final int state) {
        DrawerArrowDrawable arrowDrawable = new DrawerArrowDrawable(context);
        arrowDrawable.setProgress(state);
        arrowDrawable.setColor(Color.WHITE);

        return arrowDrawable;
    }
}
