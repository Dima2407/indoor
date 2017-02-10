package kaa_solutions.com.indoorsdk.ui.main.adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Collection;

import kaa_solutions.com.indoorsdk.R;
import kaa_solutions.com.indoorsdk.ui.main.adapters.interfaces.ISettingAdapter;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IOnChangeSettingListener;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

/**
 * Created by syn on 09.02.17.
 */

public class SettingsAdapter extends BaseAdapter implements ISettingAdapter {
    private ArrayList<SettingModel> data;
    private LayoutInflater inflater;
    private IOnChangeSettingListener onChangeListener;

    public SettingsAdapter(Context context) {
        data = new ArrayList<>();
        inflater = LayoutInflater.from(context);
    }


    @Override
    public void updateData(Collection<SettingModel> data) {
        this.data.clear();
        if (data != null) {
            this.data.addAll(data);
        }
    }

    @Override
    public void setOnChangeListener(IOnChangeSettingListener onChangeListener) {
        this.onChangeListener = onChangeListener;
    }

    @Override
    public int getCount() {
        return data.size();
    }


    @Override
    public SettingModel getItem(int position) {
        if (position < 0 || position >= data.size()) {
            return null;
        }
        return data.get(position);
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(final int position, View view, ViewGroup parent) {

        Holder holder;
        if (view == null) {
            view = inflater.inflate(R.layout.cell_setting, null);
            holder = new Holder();
            holder.textView = (TextView) view.findViewById(R.id.cell_setting_text);
            holder.aSwitch = (Switch) view.findViewById(R.id.cell_setting_switch);
            view.setTag(holder);
        } else {
            holder = (Holder) view.getTag();
        }

        SettingModel settingModel = getItem(position);
        holder.textView.setText(settingModel.getLable());
        holder.aSwitch.setChecked(settingModel.isEnable());

        holder.textView.setText(settingModel.getLable());
        holder.aSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                SettingsAdapter.this.changeState(position);
            }
        });

        return view;
    }

    private void changeState(int position) {
        SettingModel settingModel = getItem(position);
        settingModel.setEnable(!settingModel.isEnable());
        if (onChangeListener != null) {
            onChangeListener.onChange(settingModel);
        }
    }

    private class Holder {
        TextView textView;
        Switch aSwitch;
    }
}
