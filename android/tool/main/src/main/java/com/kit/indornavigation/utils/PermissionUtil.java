package com.kit.indornavigation.utils;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by ivan.k on 16.02.2016.
 */
public class PermissionUtil {
    public static final int PERMISSIONS_REQUEST_ID = 22;

    public static boolean checkPermissions(Activity activity, String... permissions) {
        List<String> notGrantedList = new ArrayList<>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(activity, permission) != PackageManager.PERMISSION_GRANTED) {
                notGrantedList.add(permission);
            }
        }
        if (notGrantedList.size() == 0) {
            return true;
        }
        ActivityCompat.requestPermissions(activity, notGrantedList.toArray(new String[notGrantedList.size()]),
                PERMISSIONS_REQUEST_ID);
        return false;
    }


    public static void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case PERMISSIONS_REQUEST_ID: {
                for (int i = 0; i < permissions.length; i++) {
                    Log.d("PermissionUtil", permissions[i] + ": " + (grantResults[i] == PackageManager
                            .PERMISSION_GRANTED ? "granted" : "not " +
                            "granted"));
                }
                return;
            }
        }
    }

    public static boolean checkAllPermissions(Activity activity) {
        List<String> permissions = new ArrayList<>();
        try {
            PackageInfo info = activity.getPackageManager().getPackageInfo(activity.getPackageName(), PackageManager
                    .GET_PERMISSIONS);
            if (info.requestedPermissions != null) {
                for (String p : info.requestedPermissions) {
                    permissions.add(p);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return checkPermissions(activity, permissions.toArray(new String[permissions.size()]));

    }


    public static boolean isGrantedPermissions(Context context, PermissionCategory category) {
        for (String permission:category.permissions){
            if( ActivityCompat.checkSelfPermission(context,permission)==PackageManager.PERMISSION_GRANTED){
                continue;
            }else {
                return false;
            }
        }
        return true;
    }
    public static boolean isGrantedPermissions(Context context, String... permissions) {
        for (String permission:permissions){
            if( ActivityCompat.checkSelfPermission(context,permission)==PackageManager.PERMISSION_GRANTED){
                continue;
            }else {
                return false;
            }
        }
        return true;
    }

    public static boolean isGrantedPermission(Context context, String permission) {
        return ActivityCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_DENIED;
    }


    private enum PermissionCategory {
        Location(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission
                .ACCESS_COARSE_LOCATION});

        private String[] permissions;

        PermissionCategory(String[] permissions) {
            this.permissions = permissions;
        }

        public String[] getPermissions(){
            return this.permissions;
        }
    }
}
