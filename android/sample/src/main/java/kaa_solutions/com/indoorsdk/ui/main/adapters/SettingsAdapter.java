package kaa_solutions.com.indoorsdk.ui.main.adapters;

import android.content.Context;
import android.widget.ArrayAdapter;
import pro.i_it.indoor.model.SettingModel;

public class SettingsAdapter extends ArrayAdapter<SettingModel> {

    public SettingsAdapter(Context context) {
        super(context, android.R.layout.simple_list_item_checked);
    }
}
