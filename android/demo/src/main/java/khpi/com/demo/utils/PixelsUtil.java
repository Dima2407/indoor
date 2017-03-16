package khpi.com.demo.utils;

import android.content.Context;
import android.util.DisplayMetrics;

public final class PixelsUtil {

    public static int dpToPx(int dp, Context context) {
        DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
        return Math.round(dp * displayMetrics.density);
    }

    public static int spToPx(int sp, Context context) {
        DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
        return Math.round(sp * displayMetrics.scaledDensity);
    }

    public static int pxToDp(int px, Context context) {
        DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
        return Math.round(px / displayMetrics.density);
    }

    public static int pxToSp(int px, Context context) {
        DisplayMetrics displayMetrics = context.getResources().getDisplayMetrics();
        return Math.round(px / displayMetrics.scaledDensity);
    }
}