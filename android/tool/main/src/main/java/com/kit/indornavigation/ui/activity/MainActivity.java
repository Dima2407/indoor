package com.kit.indornavigation.ui.activity;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Window;
import android.widget.Toast;

import com.github.alwayswannasleep.models.IndoorMap;
import com.github.alwayswannasleep.network.Callback;
import com.kit.indornavigation.R;
import com.kit.indornavigation.core.App;
import com.kit.indornavigation.ui.adapter.AbstractRecyclerAdapter;
import com.kit.indornavigation.ui.adapter.IndoorMapsAdapter;

import java.util.List;

import butterknife.Bind;

public class MainActivity extends BaseActivity {

    @Bind(R.id.toolbar)
    Toolbar toolbar;

    @Bind(R.id.list)
    RecyclerView recyclerView;
    private IndoorMapsAdapter indoorMapsAdapter;

    public static void start(final Context context) {
        context.startActivity(new Intent(context, MainActivity.class));
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        indoorMapsAdapter = new IndoorMapsAdapter();

        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(indoorMapsAdapter);

        indoorMapsAdapter.setClickListener(new AbstractRecyclerAdapter.OnClickListener<IndoorMap>() {
            @Override
            public void onClick(View v, IndoorMap item, int position) {
                IndoorMapDetailsActivity.start(MainActivity.this, item);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        app.getNetBridge().loadMaps(new Callback() {
            @Override
            protected void onSuccessUi() {
                List<IndoorMap> indoorMaps = getData();
                indoorMapsAdapter.setItems(indoorMaps);
            }

            @Override
            protected void onErrorUi(final int code) {
                if (!isOnline())
                    Toast.makeText(app, "No connecting", Toast.LENGTH_SHORT).show();
                else
                    Toast.makeText(app, "Error loading items", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private boolean isOnline() {
        ConnectivityManager cm = (ConnectivityManager)this.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo netInfo = cm.getActiveNetworkInfo();
        if (netInfo != null && netInfo.isConnectedOrConnecting())
            return true;
        return false;
    }

    @Override
    public int getLayResId() {
        return R.layout.activity_poi_details;
    }
}