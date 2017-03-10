package kaa_solutions.com.indoorsdk.ui.main.adapters.interfaces;

import java.util.Collection;

import kaa_solutions.com.indoorsdk.ui.main.interfaces.IOnChangeSettingListener;
import pro.i_it.indoor.model.SettingModel;

/**
 * Created by syn on 09.02.17.
 */

public interface ISettingAdapter {
    void updateData(Collection<SettingModel> data);

    void setOnChangeListener(IOnChangeSettingListener onChangeListener);
}
