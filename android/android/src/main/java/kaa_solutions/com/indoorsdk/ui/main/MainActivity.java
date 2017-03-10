package kaa_solutions.com.indoorsdk.ui.main;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ListView;

import java.util.Collection;

import kaa_solutions.com.indoorsdk.IndoorSdk;
import kaa_solutions.com.indoorsdk.R;
import kaa_solutions.com.indoorsdk.ui.main.adapters.SettingsAdapter;
import kaa_solutions.com.indoorsdk.ui.main.adapters.interfaces.ISettingAdapter;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivity;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivityPresenter;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IOnChangeSettingListener;
import pro.i_it.indoor.model.SettingModel;

public class MainActivity extends AppCompatActivity implements IMainActivity {
    private IMainActivityPresenter presenter;
    private ISettingAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        IndoorSdk.initIndoorSdk(this);
        baseInit();
        initView();

        presenter.init(this);
    }


    private void baseInit() {
        presenter = new MainActivityPresenter();
    }

    private void initView() {
        ListView settingsListView = (ListView) findViewById(R.id.activity_main_list);
        SettingsAdapter settingsAdapter = new SettingsAdapter(this);
        settingsListView.setAdapter(settingsAdapter);
        adapter = settingsAdapter;
    }

    @Override
    public Context getContext() {
        return this;
    }

    @Override
    public void updateData(Collection<SettingModel> data) {
        adapter.updateData(data);
    }

    @Override
    public void setOnChangeConfig(IOnChangeSettingListener listener) {
        adapter.setOnChangeListener(listener);
    }

    @Override
    public Activity getActivity() {
        return this;
    }
}
