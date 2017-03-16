package khpi.com.demo.ui.fragment;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import khpi.com.demo.R;
import khpi.com.demo.model.Building;


public final class IndoorFragment extends GenericFragment {

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.indoor_fragment, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        Bundle arguments = getArguments();
        final Building building = arguments.getParcelable("map");
    }

    @Override
    public void onStart() {
        super.onStart();
//        IndoorPositionManager.getInstance(getActivity());
    }

    @Override
    public void onStop() {
        super.onStop();
        //IndoorPositionManager.release();
    }

    public static Fragment makeInstance(Building building) {
        IndoorFragment fragment = new IndoorFragment();
        Bundle bundle = new Bundle();
        bundle.putParcelable("map", building);
        fragment.setArguments(bundle);
        return fragment;
    }
}
