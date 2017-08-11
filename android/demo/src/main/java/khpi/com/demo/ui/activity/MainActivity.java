package khpi.com.demo.ui.activity;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.TabLayout;
import android.support.v7.graphics.drawable.DrawerArrowDrawable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import khpi.com.demo.R;
import khpi.com.demo.core.GRApplication;
import khpi.com.demo.ui.BottomSheet;
import khpi.com.demo.ui.adapter.RouteDataAdapter;

public final class MainActivity extends GenericActivity {

    private static final int REQUEST_PERMISSION = 100;

    private BottomSheet bottomSheet;


    @SuppressWarnings("ConstantConditions")
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        DrawerArrowDrawable indicator = new DrawerArrowDrawable(this);
        indicator.setProgress(1);
        indicator.setColor(Color.WHITE);

        getSupportActionBar().setHomeAsUpIndicator(indicator);

        View bottomSheet = findViewById(R.id.bottom_sheet);
        View layout = findViewById(R.id.layout);

        this.bottomSheet = new BottomSheet(bottomSheet, layout);
        this.bottomSheet.getDataList().setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false));
        this.bottomSheet.getDataList().setAdapter(new RouteDataAdapter(this));

        getLauncher().launchIndoorMapsFragment();
    }

    @Override
    public BottomSheet getBottomSheet() {
        return bottomSheet;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);

        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        switch (id) {
            case R.id.main_menu_settings_btn:
                onSettingsBtnPressed();
                break;
            case android.R.id.home:
                onBackPressed();
                break;
        }

        return true;
    }

    private void onSettingsBtnPressed() {
        SettingsActivity.start(this);
    }

    @Override
    public void onBackPressed() {
        getLauncher().launchIndoorMapsFragment();
        getSupportActionBar().setDisplayHomeAsUpEnabled(false);
    }

    public static void start(Activity activity) {
        activity.startActivity(new Intent(activity, MainActivity.class));
    }
}
