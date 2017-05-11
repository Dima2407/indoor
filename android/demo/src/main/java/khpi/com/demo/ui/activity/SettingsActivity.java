package khpi.com.demo.ui.activity;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.IntentCompat;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;
import android.support.v7.widget.Toolbar;
import android.widget.CompoundButton;
import android.widget.Switch;

import khpi.com.demo.R;

public final class SettingsActivity extends GenericActivity {

    private boolean wasServerChanged;

    public static void start(Activity activity) {
        activity.startActivity(new Intent(activity, SettingsActivity.class));
    }

    @SuppressWarnings("ConstantConditions")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        DrawerArrowDrawable indicator = new DrawerArrowDrawable(this);
        indicator.setProgress(1);
        indicator.setColor(Color.WHITE);

        getSupportActionBar().setHomeAsUpIndicator(indicator);

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

        Switch useBinaryMask = (Switch) findViewById(R.id.settings_use_binary_mask);
        useBinaryMask.setChecked(getProjectApplication().getSharedHelper().useBinaryMask());

        useBinaryMask.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                getProjectApplication().getSharedHelper().setUseBinaryMask(isChecked);
            }
        });


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
