package khpi.com.demo.ui.fragment;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import khpi.com.demo.BuildConfig;
import khpi.com.demo.R;
import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.model.Building;
import khpi.com.demo.model.Floor;
import khpi.com.demo.net.MapCacheHelper;
import khpi.com.demo.ui.adapter.AbstractRecyclerAdapter;
import khpi.com.demo.ui.adapter.BuildingAdapter;
import khpi.com.demo.utils.NetUtil;

import java.io.File;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

public class BuildingsFragment extends GenericFragment
        implements AbstractRecyclerAdapter.OnClickListener<Building>, NetUtil.NetFileListener, Observer {

    private RecyclerView recycler;
    private BuildingAdapter buildingAdapter;
    private ProgressDialog progressDialog;
    private Floor floor;
    public static String KEY_BUILD_ID = "buildId";

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_indors_map, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        recycler = (RecyclerView) view.findViewById(R.id.recycler);
        recycler.setLayoutManager(new LinearLayoutManager(getActivity()));

        buildingAdapter = new BuildingAdapter();
        recycler.setAdapter(buildingAdapter);
        buildingAdapter.setClickListener(this);
        List<Building> buildings = getActivityBridge().getDbBridge().getBuildings();
        buildingAdapter.addItems(buildings);
    }

    @Override
    public void onStart() {
        super.onStart();
        getActivityBridge().getDbBridge().addObserver(this);
    }

    @Override
    public void onStop() {
        super.onStop();
        getActivityBridge().getDbBridge().deleteObserver(this);
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public void onClick(View v, Building item, int position) {
        if(getActivityBridge().getDbBridge().getFloorsByBuildingId(item.getId()).size() == 1){
            floor = getActivityBridge().getDbBridge().getFloorsByBuildingId(item.getId()).get(0);
            progressDialog = new ProgressDialog(getContext());
            progressDialog.setMessage("Wait...");
            progressDialog.show();
            getActivityBridge().getProjectApplication().getMapCacheHelper()
                    .cacheMapData(floor, this);
            getActivityBridge().getNetBridge().loadInpointsByBuildingId(item.getId());
            return;
        }
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        FloorsFragment floorsFragment = new FloorsFragment();
        Bundle bundle = new Bundle();
        bundle.putLong(KEY_BUILD_ID, item.getId());
        floorsFragment.setArguments(bundle);
        ft.replace(R.id.fragment_container, floorsFragment);
        ft.isAddToBackStackAllowed();
        ft.commit();
    }

    @Override
    public void update(Observable o, Object arg) {
        if (arg.equals(DbBridge.BUILDINGS_UPDATED)) {
            List<Building> buildings = getActivityBridge().getDbBridge().getBuildings();
            buildingAdapter.clear();
            buildingAdapter.addItems(buildings);
            return;
        }

    }

    @Override
    public void onError(Throwable throwable) {

    }

    @Override
    public void onSuccess(File result) {
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                progressDialog.dismiss();
                getActivityBridge().getLauncher().launchIndoorMapFragment(floor);
            }
        });
    }

    @Override
    public void onProgress(int done, int total) {

    }
}
