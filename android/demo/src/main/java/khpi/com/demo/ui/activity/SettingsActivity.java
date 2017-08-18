package khpi.com.demo.ui.activity;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.PointF;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.IntentCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Switch;

import khpi.com.demo.R;
import khpi.com.demo.core.SharedHelper;

public final class SettingsActivity extends GenericActivity {

    private boolean wasServerChanged;
    private EditText xPosition;
    private EditText yPosition;
    private Switch bleSwitch;
    private Switch sensorSwitch;
    private Switch beaconMod1Switch;
    private Switch beaconMod2Switch;
    private Switch beaconMod3Switch;
    private Switch sensorMod1Switch;
    private Switch sensorMod2Switch;
    private Switch sensorMod3Switch;
    private Switch settingMapCorrSwitch;
    private Switch settingMeshCorrSwitch;
    private Switch settingWallCorrSwitch;
    private Switch settingLoggerSwitch;
    private Switch particlefilterSwitch;
    private LinearLayout beaconModsLayout;
    private LinearLayout sensorModsLayout;
    private LinearLayout settingsWallCorrLayout;

    private LinearLayout sensorSettingInitLayout;

    private boolean modActivated;

    public static void start(Activity activity) {
        activity.startActivity(new Intent(activity, SettingsActivity.class));
    }

    @SuppressWarnings("ConstantConditions")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        final DrawerArrowDrawable indicator = new DrawerArrowDrawable(this);
        indicator.setProgress(1);
        indicator.setColor(Color.WHITE);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        toolbar.setNavigationIcon(indicator);
        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                onBackPressed();
            }

        });

        //setSupportActionBar(toolbar);
        //getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        //getSupportActionBar().setHomeAsUpIndicator(indicator);

        Switch useProduction = (Switch) findViewById(R.id.settings_use_production_server);
        useProduction.setChecked(getProjectApplication().getSharedHelper().useProduction());

        useProduction.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                getProjectApplication().getSharedHelper().setUseProduction(b);
                wasServerChanged = true;
            }
        });

        Switch inRadar = (Switch) findViewById(R.id.settings_in_radar);
        inRadar.setChecked(getProjectApplication().getSharedHelper().drawInRadar());

        inRadar.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                getProjectApplication().getSharedHelper().setDrawInRadar(b);
            }
        });

        bleSwitch = (Switch) findViewById(R.id.ble_beacons_switch);
        sensorSwitch = (Switch) findViewById(R.id.sensor_switch);
        beaconModsLayout = (LinearLayout) findViewById(R.id.beacon_mod_group);
        sensorModsLayout = (LinearLayout) findViewById(R.id.sensor_mod_group);
        settingsWallCorrLayout = (LinearLayout) findViewById(R.id.settings_wall_corr_layout);

        bleSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    updateActiveBLESubmode();
                    beaconModsLayout.setVisibility(View.VISIBLE);
                    settingWallCorrSwitch.setChecked(false);
                    settingsWallCorrLayout.setVisibility(View.GONE);
                    sensorSwitch.setChecked(false);
                    particlefilterSwitch.setChecked(false);
                    sensorModsLayout.setVisibility(View.GONE);
                } else if (sensorSwitch.isChecked() && !particlefilterSwitch.isChecked()) {
                    sensorSwitch.setChecked(true);
                    settingsWallCorrLayout.setVisibility(View.VISIBLE);
                } else {
                    particlefilterSwitch.setChecked(true);
                    settingsWallCorrLayout.setVisibility(View.VISIBLE);

                }
            }
        });


        sensorSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    int submode = getProjectApplication().getSharedHelper().getSensorsSubMode();
                    updateActiveSensorSubmode(submode);
                    sensorModsLayout.setVisibility(View.VISIBLE);

                    bleSwitch.setChecked(false);
                    particlefilterSwitch.setChecked(false);
                    if (!particlefilterSwitch.isChecked()) {
                        beaconModsLayout.setVisibility(View.GONE);
                    }
                } else if (bleSwitch.isChecked() && !particlefilterSwitch.isChecked()) {
                    bleSwitch.setChecked(true);
                    sensorModsLayout.setVisibility(View.GONE);
                } else {
                    particlefilterSwitch.setChecked(true);
                }
            }
        });

        beaconMod1Switch = (Switch) findViewById(R.id.ble_switch_mod_1);
        beaconMod2Switch = (Switch) findViewById(R.id.ble_switch_mod_2);
        beaconMod3Switch = (Switch) findViewById(R.id.ble_switch_mod_3);

        beaconMod1Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    beaconMod1Switch.setChecked(true);
                    beaconMod2Switch.setChecked(false);
                } else if (!beaconMod2Switch.isChecked()) {
                    beaconMod1Switch.setChecked(true);
                }

            }
        });

        beaconMod2Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    beaconMod1Switch.setChecked(false);
                    beaconMod2Switch.setChecked(true);
                } else if (!beaconMod1Switch.isChecked()) {
                    beaconMod2Switch.setChecked(true);
                }
            }
        });

        beaconMod3Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    beaconMod3Switch.setChecked(true);
                }
            }
        });

        sensorMod1Switch = (Switch) findViewById(R.id.sensor_switch_mod_1);
        sensorMod2Switch = (Switch) findViewById(R.id.sensor_switch_mod_2);
        sensorMod3Switch = (Switch) findViewById(R.id.sensor_switch_mod_3);
        sensorSettingInitLayout = (LinearLayout) findViewById(R.id.settings_init_position);

        sensorMod1Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    updateInitPosition(SharedHelper.MODE_SENSORS, SharedHelper.SUB_MODE_SENSORS_1);
                    sensorMod2Switch.setChecked(false);
                    sensorMod3Switch.setChecked(false);

                } else if (!sensorMod2Switch.isChecked() && !sensorMod3Switch.isChecked()) {
                    sensorMod1Switch.setChecked(true);
                } else {
                    sensorSettingInitLayout.setVisibility(View.GONE);
                }
            }
        });

        sensorMod2Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    sensorSettingInitLayout.setVisibility(View.GONE);
                    sensorMod1Switch.setChecked(false);
                    sensorMod3Switch.setChecked(false);

                } else if (!sensorMod1Switch.isChecked() && !sensorMod3Switch.isChecked()) {
                    sensorMod2Switch.setChecked(true);
                }
            }
        });

        sensorMod3Switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                if (isChecked) {
                    sensorSettingInitLayout.setVisibility(View.GONE);
                    sensorMod1Switch.setChecked(false);
                    sensorMod2Switch.setChecked(false);

                } else if (!sensorMod1Switch.isChecked() && !sensorMod2Switch.isChecked()) {
                    sensorMod3Switch.setChecked(true);
                }
            }
        });

        xPosition = (EditText) findViewById(R.id.settings_init_position_x);
        yPosition = (EditText) findViewById(R.id.settings_init_position_y);

        settingMapCorrSwitch = (Switch) findViewById(R.id.setting_map_switch);
        settingMapCorrSwitch.setChecked(getProjectApplication().getSharedHelper().useMapCoordinateCorrection());
        settingMapCorrSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    settingMapCorrSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setMapCoordinateCorrection(true);
                } else {
                    settingMapCorrSwitch.setChecked(false);
                    getProjectApplication().getSharedHelper().setMapCoordinateCorrection(false);
                }
            }
        });

        settingMeshCorrSwitch = (Switch) findViewById(R.id.setting_mesh_switch);
        settingMeshCorrSwitch.setChecked(getProjectApplication().getSharedHelper().useMeshCoordinateCorrection());
        settingMeshCorrSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    settingMeshCorrSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setMeshCoordinateCorrection(true);
                } else {
                    settingMeshCorrSwitch.setChecked(false);
                    getProjectApplication().getSharedHelper().setMeshCoordinateCorrection(false);
                }
            }
        });

        settingWallCorrSwitch = (Switch) findViewById(R.id.setting_walls_switch);
        settingWallCorrSwitch.setChecked(getProjectApplication().getSharedHelper().useWallCoordinateCorrection());
        settingWallCorrSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    settingWallCorrSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setWallCoordinateCorrection(true);
                } else {
                    settingWallCorrSwitch.setChecked(false);
                    getProjectApplication().getSharedHelper().setWallCoordinateCorrection(false);
                }
            }
        });

        settingLoggerSwitch = (Switch) findViewById(R.id.setting_logger_switch);
        settingLoggerSwitch.setChecked(getProjectApplication().getSharedHelper().isLoggerEnable());
        settingLoggerSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    settingLoggerSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setLoggerEnable(true);
                } else {
                    settingLoggerSwitch.setChecked(false);
                    getProjectApplication().getSharedHelper().setLoggerEnable(false);
                }
            }
        });

        particlefilterSwitch = (Switch) findViewById(R.id.particle_filter_switch);
        particlefilterSwitch.setChecked(getProjectApplication().getSharedHelper().isParticleFilterEnable());
        particlefilterSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    particlefilterSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setParticleFilterEnable(true);
                    beaconModsLayout.setVisibility(View.VISIBLE);
                    sensorModsLayout.setVisibility(View.VISIBLE);
                    bleSwitch.setChecked(false);
                    sensorSwitch.setChecked(false);
                } else if (!bleSwitch.isChecked() && !sensorSwitch.isChecked()) {
                    particlefilterSwitch.setChecked(true);
                    getProjectApplication().getSharedHelper().setParticleFilterEnable(false);
                }
            }
        });


    }

    private void updateInitPosition(int activeModeKey, int submode) {
        if ((activeModeKey == SharedHelper.MODE_SENSORS || activeModeKey == SharedHelper.MODE_MIXIN)
                && submode == SharedHelper.SUB_MODE_SENSORS_1) {
            PointF initPosition = getProjectApplication().getSharedHelper().getInitPosition();
            xPosition.setText(String.valueOf(initPosition.x));
            yPosition.setText(String.valueOf(initPosition.y));
            findViewById(R.id.settings_init_position).setVisibility(View.VISIBLE);
        } else {
            findViewById(R.id.settings_init_position).setVisibility(View.GONE);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        int activeMode = getProjectApplication().getSharedHelper().getActiveModeKey();
        if (activeMode == SharedHelper.MODE_BLE) {
            beaconModsLayout.setVisibility(View.VISIBLE);
            sensorModsLayout.setVisibility(View.GONE);
            bleSwitch.setChecked(true);
            sensorSwitch.setChecked(false);
            updateActiveBLESubmode();
        } else if (activeMode == SharedHelper.MODE_SENSORS) {
            beaconModsLayout.setVisibility(View.GONE);
            sensorModsLayout.setVisibility(View.VISIBLE);
            sensorSwitch.setChecked(true);
            bleSwitch.setChecked(false);
            int submode = getProjectApplication().getSharedHelper().getSensorsSubMode();
            updateActiveSensorSubmode(submode);
        } else if (activeMode == SharedHelper.MODE_MIXIN) {
            beaconModsLayout.setVisibility(View.VISIBLE);
            sensorModsLayout.setVisibility(View.VISIBLE);
            bleSwitch.setChecked(false);
            sensorSwitch.setChecked(false);
            updateActiveBLESubmode();
            int submode = getProjectApplication().getSharedHelper().getSensorsSubMode();
            updateActiveSensorSubmode(submode);
        } else {
            sensorSwitch.setChecked(true);
            bleSwitch.setChecked(false);
            beaconModsLayout.setVisibility(View.GONE);
            sensorModsLayout.setVisibility(View.VISIBLE);
            updateActiveBLESubmode();
        }
        updateInitPosition(activeMode,
                getProjectApplication().getSharedHelper().getSensorsSubMode());
    }

    private void updateActiveSensorSubmode(int submode) {
        if (submode == SharedHelper.SUB_MODE_SENSORS_1) {
            sensorMod1Switch.setChecked(true);
            sensorMod2Switch.setChecked(false);
            sensorMod3Switch.setChecked(false);
        } else if (submode == SharedHelper.SUB_MODE_SENSORS_2) {
            sensorMod1Switch.setChecked(false);
            sensorMod2Switch.setChecked(true);
            sensorMod3Switch.setChecked(false);
        } else if (submode == SharedHelper.SUB_MODE_SENSORS_3) {
            sensorMod1Switch.setChecked(false);
            sensorMod2Switch.setChecked(false);
            sensorMod3Switch.setChecked(true);
        } else {
            sensorMod1Switch.setChecked(false);
            sensorMod2Switch.setChecked(true);
            sensorMod3Switch.setChecked(false);
        }
    }

    private void updateActiveBLESubmode() {
        int submode = getProjectApplication().getSharedHelper().getBLESubMode();
        boolean enabled = getProjectApplication().getSharedHelper().isMultiLaterationEnabled();
        if (submode == SharedHelper.SUB_MODE_BLE_1) {
            beaconMod1Switch.setChecked(true);
            beaconMod2Switch.setChecked(false);
        } else if (submode == SharedHelper.SUB_MODE_BLE_2) {
            beaconMod1Switch.setChecked(false);
            beaconMod2Switch.setChecked(true);
        } else {
            beaconMod1Switch.setChecked(true);
            beaconMod2Switch.setChecked(false);
        }
        beaconMod3Switch.setChecked(enabled);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (bleSwitch.isChecked()) {
            getProjectApplication().getSharedHelper().setActiveModeKey(SharedHelper.MODE_BLE);
            getProjectApplication().getSharedHelper().setSensorsSubMode(-1);
            getProjectApplication().getSharedHelper().setMultiLaterationEnabled(beaconMod3Switch.isChecked());
        } else if (sensorSwitch.isChecked()) {
            getProjectApplication().getSharedHelper().setActiveModeKey(SharedHelper.MODE_SENSORS);
            getProjectApplication().getSharedHelper().setBLESubMode(-1);
        } else if (particlefilterSwitch.isChecked()) {
            getProjectApplication().getSharedHelper().setParticleFilterEnable(true);
            getProjectApplication().getSharedHelper().setActiveModeKey(SharedHelper.MODE_MIXIN);
            getProjectApplication().getSharedHelper().setMultiLaterationEnabled(beaconMod3Switch.isChecked());
        } else {
            getProjectApplication().getSharedHelper().setActiveModeKey(SharedHelper.MODE_BLE);
            getProjectApplication().getSharedHelper().setSensorsSubMode(-1);
        }

        if (getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_BLE
                || getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_MIXIN) {
            if (beaconMod1Switch.isChecked()) {
                getProjectApplication().getSharedHelper().setBLESubMode(SharedHelper.SUB_MODE_BLE_1);
            } else if (beaconMod2Switch.isChecked()) {
                getProjectApplication().getSharedHelper().setBLESubMode(SharedHelper.SUB_MODE_BLE_2);
            } else {
                getProjectApplication().getSharedHelper().setBLESubMode(SharedHelper.SUB_MODE_BLE_1);
            }
        }

        if (getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_SENSORS
                || getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_MIXIN) {
            if (sensorMod1Switch.isChecked()) {
                getProjectApplication().getSharedHelper().setSensorsSubMode(SharedHelper.SUB_MODE_SENSORS_1);
            } else if (sensorMod2Switch.isChecked()) {
                getProjectApplication().getSharedHelper().setSensorsSubMode(SharedHelper.SUB_MODE_SENSORS_2);
            } else if (sensorMod3Switch.isChecked()) {
                getProjectApplication().getSharedHelper().setSensorsSubMode(SharedHelper.SUB_MODE_SENSORS_3);
            } else {
                getProjectApplication().getSharedHelper().setSensorsSubMode(SharedHelper.SUB_MODE_SENSORS_2);
            }
        }
        if ((getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_SENSORS
                || getProjectApplication().getSharedHelper().getActiveModeKey() == SharedHelper.MODE_MIXIN)
                && getProjectApplication().getSharedHelper().getSensorsSubMode() == SharedHelper.SUB_MODE_SENSORS_1) {
            getProjectApplication().getSharedHelper().setInitPosition(xPosition.getText().toString(),
                    yPosition.getText().toString());
        }
    }

    private void showNotSupportedModeError() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Mode not supported!!!");
        builder.setNegativeButton("OK", null);
        builder.show();
    }

    @Override
    public boolean onSupportNavigateUp() {
        if (wasServerChanged) {
            Intent intent = IntentCompat.makeRestartActivityTask(new ComponentName(getApplicationContext(), MainActivity.class));
            startActivity(intent);
            Runtime.getRuntime().exit(0);
        }

        finish();
        return true;
    }

}
