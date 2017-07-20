package khpi.com.demo.ui.activity;

import android.app.Activity;
import android.content.ComponentName;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.PointF;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.IntentCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Switch;

import khpi.com.demo.R;
import khpi.com.demo.utils.PermissionUtil;

public final class SettingsActivity extends GenericActivity {

    private boolean wasServerChanged;
    private EditText xPosition;
    private EditText yPosition;

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

        final DrawerArrowDrawable indicator = new DrawerArrowDrawable(this);
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

        xPosition = (EditText) findViewById(R.id.settings_init_position_x);
        yPosition = (EditText) findViewById(R.id.settings_init_position_y);
        Spinner spinner  = (Spinner) findViewById(R.id.settings_mode_spinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.modes, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spinner.setAdapter(adapter);

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                int activeModeKey = getProjectApplication().getSharedHelper().getActiveModeKey();
                switch (position){
                    case 0:
                    case 1:
                    case 2:
                        activeModeKey = position;
                        getProjectApplication().getSharedHelper().setActiveModeKey(activeModeKey);
                        break;
                    case 3:
                    case 4:
                        parent.setSelection(activeModeKey);
                        showNotSupportedModeError();
                        break;

                }
                updateInitPosition(activeModeKey);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

    }

    private void updateInitPosition(int activeModeKey) {
        if(activeModeKey == 1){
            PointF initPosition = getProjectApplication().getSharedHelper().getInitPosition();
            xPosition.setText(String.valueOf(initPosition.x));
            yPosition.setText(String.valueOf(initPosition.y));
            findViewById(R.id.settings_init_position).setVisibility(View.VISIBLE);
        }else {
            findViewById(R.id.settings_init_position).setVisibility(View.GONE);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        updateInitPosition(getProjectApplication().getSharedHelper().getActiveModeKey());
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(getProjectApplication().getSharedHelper().getActiveModeKey() == 1){
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
