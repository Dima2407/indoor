package khpi.com.demo.ui.activity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;

import khpi.com.demo.R;
import khpi.com.demo.utils.PermissionUtil;


public class SplashActivity extends GenericActivity {
    private static final int REQUEST_ENABLE_BT = 25;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera_outdoor);
    }


    @Override
    protected void onResume() {
        super.onResume();

        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Bluetooth LE not supported by this device");
            builder.setNegativeButton("EXIT", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    finish();
                }
            });
            builder.create().show();
            return;
        } else {
            if (!mBluetoothAdapter.isEnabled()) {
                enableBluetooth();
                return;
            }
        }
        MainActivity.start(this);
        finish();

    }

    private void enableBluetooth() {
        new AlertDialog.Builder(this)
                .setTitle("Enable Bluetooth")
                .setMessage("Please enable bluetooth")
                .setPositiveButton("Enable", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                        startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
                    }
                })
                .setNegativeButton("Close", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        SplashActivity.this.finish();
                    }
                })
                .create()
                .show();
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
            finish();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[]
            grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        MainActivity.start(this);
        finish();
    }

}
