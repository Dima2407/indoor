package kaa_solutions.com.indoorsdk.ui.main;

import android.app.Activity;
import android.app.ListActivity;
import android.content.Context;
import android.os.Bundle;
import android.util.SparseBooleanArray;
import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import kaa_solutions.com.indoorsdk.IndoorSdk;
import kaa_solutions.com.indoorsdk.ui.main.adapters.SettingsAdapter;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivity;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivityPresenter;
import pro.i_it.indoor.model.SettingModel;

import java.util.Collection;

public class MainActivity extends ListActivity implements IMainActivity {
    private IMainActivityPresenter presenter;
    private SettingsAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        IndoorSdk.initIndoorSdk(this);
        baseInit();
        initView();

        presenter.init(this);
        getListView().setChoiceMode(AbsListView.CHOICE_MODE_MULTIPLE);
        getListView().setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                final SparseBooleanArray itemChecked = getListView().getCheckedItemPositions();
                for (int i = 0; i < itemChecked.size(); i++) {
                    final SettingModel item = adapter.getItem(itemChecked.keyAt(i));
                    item.setEnable(itemChecked.valueAt(i));
                }
            }
        });
    }


    private void baseInit() {
        presenter = new MainActivityPresenter();
    }

    private void initView() {
        adapter = new SettingsAdapter(this);
        setListAdapter(adapter);
    }

    @Override
    public Context getContext() {
        return this;
    }

    @Override
    public void updateData(Collection<SettingModel> data) {
        if (adapter.getCount() > 0) {
            adapter.clear();
        }
        adapter.addAll(data);
    }

    @Override
    public Activity getActivity() {
        return this;
    }
}
