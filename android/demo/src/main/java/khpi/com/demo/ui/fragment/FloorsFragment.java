package khpi.com.demo.ui.fragment;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import khpi.com.demo.R;
import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.model.Floor;
import khpi.com.demo.net.MapCacheHelper;
import khpi.com.demo.ui.adapter.AbstractRecyclerAdapter;
import khpi.com.demo.ui.adapter.FloorAdapter;
import khpi.com.demo.utils.NetUtil;

import java.io.File;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

public class FloorsFragment extends GenericFragment implements AbstractRecyclerAdapter.OnClickListener<Floor>, NetUtil.NetFileListener, Observer {

    RecyclerView recycler;
    private FloorAdapter floorAdapter;
    private ProgressDialog progressDialog;
    private Floor item;
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
        Bundle mBundle = new Bundle();
        mBundle = getArguments();
        long buildingId = mBundle.getLong("build");
        floorAdapter = new FloorAdapter();
        recycler.setAdapter(floorAdapter);
        floorAdapter.setClickListener(this);
        List<Floor> floors = getActivityBridge().getDbBridge().getFloorsByBuildingId(buildingId);
        floorAdapter.addItems(floors);
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
    public void onClick(View v, Floor item, int position) {
        this.item = item;
        progressDialog = new ProgressDialog(getContext());
        progressDialog.setMessage("Wait...");
        progressDialog.show();
        getActivityBridge().getNetBridge().loadInpointsByBuildingId(item.getId());
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
                getActivityBridge().getLauncher().launchIndoorMapFragment(item);
            }
        });
    }

    @Override
    public void onProgress(int done, int total) {

    }

    @Override
    public void update(Observable o, Object arg) {
        if (arg.equals(DbBridge.FLOORS_UPDATED)) {
            List<Floor> floors = getActivityBridge().getDbBridge().getFloorsByBuildingId(item.getBuildingId());
            floorAdapter.clear();
            floorAdapter.addItems(floors);
            return;
        }
        if(arg.equals(DbBridge.INPOINTS_UPDATED)){
            MapCacheHelper.cacheMapData(getContext(), item, this);
            return;
        }
    }
}
