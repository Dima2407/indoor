package kaa_solutions.com.indoorsdk.ui.main.interfaces;

import android.app.Activity;
import android.content.Context;

import java.util.Collection;

import pro.i_it.indoor.model.SettingModel;

/**
 * Created by syn on 09.02.17.
 */

public interface IMainActivity {

    Context getContext();

    void updateData(Collection<SettingModel> data);

    Activity getActivity();
}
