package khpi.com.demo.ui.fragment;

import android.content.Context;

import khpi.com.demo.core.bridge.ActivityBridge;

abstract class GenericFragment extends android.support.v4.app.Fragment {

    private ActivityBridge activityBridge;

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);

        activityBridge = (ActivityBridge) getActivity();
    }

    protected ActivityBridge getActivityBridge() {
        return activityBridge;
    }
}
