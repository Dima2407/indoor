package kaa_solutions.com.indoorsdk.ui.main.interfaces;

import android.app.Activity;
import android.content.Context;

import java.util.Collection;

import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

/**
 * Created by syn on 09.02.17.
 */

public interface IMainActivity {

    Context getContext();

    void updateData(Collection<SettingModel> data);

    void setOnChangeConfig(IOnChangeSettingListener listener);


    Activity getActivity();
}
