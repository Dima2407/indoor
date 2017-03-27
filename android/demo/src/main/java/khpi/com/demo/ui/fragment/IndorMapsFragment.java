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
import khpi.com.demo.model.Building;
import khpi.com.demo.ui.adapter.AbstractRecyclerAdapter;
import khpi.com.demo.ui.adapter.BuildingAdapter;

import java.util.List;
import java.util.Observable;
import java.util.Observer;

public class IndorMapsFragment extends GenericFragment implements AbstractRecyclerAdapter.OnClickListener<Building>/*, NetUtil.NetFileListener*/, Observer {

    private RecyclerView recycler;
    private BuildingAdapter buildingAdapter;
    private ProgressDialog progressDialog;
    private Building item;
    private ProgressDialog dialog;


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
        getActivityBridge().getNetBridge().logIn(BuildConfig.USERNAME, BuildConfig.PASSWORD);
    }

    @Override
    public void onClick(View v, Building item, int position) {
//        this.item = item;
//        progressDialog = new ProgressDialog(getContext());
//        progressDialog.setMessage("Wait...");
//        progressDialog.show();
//        getActivityBridge().getNetBridge().loadInpointsByBuildingId(item.getId());
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        FloorsFragment floorsFragment = new FloorsFragment();
        Bundle bundle = new Bundle();
        final String key = "build";
        bundle.putLong(key, item.getId());
        floorsFragment.setArguments(bundle);
        ft.replace(R.id.fragment_container, floorsFragment);
        ft.isAddToBackStackAllowed();
        ft.commit();
    }

//    @Override
//    public void onError(Throwable throwable) {
//
//    }
//
//    @Override
//    public void onSuccess(File result) {
//        getActivity().runOnUiThread(new Runnable() {
//            @Override
//            public void run() {
//                progressDialog.dismiss();
//                getActivityBridge().getLauncher().launchIndoorMapFragment(item);
//            }
//        });
//    }
//
//    @Override
//    public void onProgress(int done, int total) {
//
//    }

    @Override
    public void update(Observable o, Object arg) {
//        if (arg.equals(DbBridge.BUILDINGS_UPDATED)) {
//            List<Building> buildings = getActivityBridge().getDbBridge().getBuildings();
//            buildingAdapter.clear();
//            buildingAdapter.addItems(buildings);
//            return;
//        }
//        if(arg.equals(DbBridge.INPOINTS_UPDATED)){
//            MapCacheHelper.cacheMapData(getContext(), item, this);
//            return;
//        }
    }
}