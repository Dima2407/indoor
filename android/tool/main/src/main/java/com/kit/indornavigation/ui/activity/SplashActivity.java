package com.kit.indornavigation.ui.activity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.support.annotation.NonNull;
import android.widget.Toast;

import com.github.alwayswannasleep.network.Callback;
import com.kit.indornavigation.R;
import com.kit.indornavigation.utils.PermissionUtil;

public class SplashActivity extends BaseActivity {
    private static final int REQUEST_ENABLE_BT = 25;


    @Override
    protected void onResume() {
        super.onResume();

        if (PermissionUtil.checkAllPermissions(this)) {
            app.getNetBridge().login(new Callback() {

                @Override
                protected void onSuccessUi() {
                    MainActivity.start(SplashActivity.this);
                    finish();
                }

                @Override
                protected void onErrorUi(int code) {
                    if (!isOnline())
                        Toast.makeText(app, "No connecting", Toast.LENGTH_SHORT).show();
                    else
                        Toast.makeText(SplashActivity.this, "Error logging in", Toast.LENGTH_SHORT).show();
                }
            });
        }
    }

    private boolean isOnline() {
        ConnectivityManager cm = (ConnectivityManager)this.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo netInfo = cm.getActiveNetworkInfo();
        if (netInfo != null && netInfo.isConnectedOrConnecting())
            return true;
        return false;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode != REQUEST_ENABLE_BT || resultCode != Activity.RESULT_OK) {
            finish();
            return;
        }

        if (PermissionUtil.checkAllPermissions(this)) {
            MainActivity.start(this);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[]
            grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        MainActivity.start(this);
    }

    @Override
    public int getLayResId() {
        return R.layout.activity_splash;
    }
}
