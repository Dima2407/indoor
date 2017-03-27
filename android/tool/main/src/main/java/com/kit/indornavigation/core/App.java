package com.kit.indornavigation.core;

import android.app.Application;

import com.github.alwayswannasleep.network.NetBridge;
import com.github.alwayswannasleep.network.NetFacade;
import com.jakewharton.picasso.OkHttp3Downloader;
import com.kit.indornavigation.BuildConfig;
import com.squareup.picasso.Picasso;

import okhttp3.OkHttpClient;

public class App extends Application {

    private BeaconSearcher beaconSearcher;
    private AlgoManager algoManager;
    private NetBridge netBridge;

    @Override
    public void onCreate() {
        super.onCreate();
        beaconSearcher = new BeaconSearcher(this);
        algoManager = new AlgoManager(this);
        netBridge = NetFacade.instantiate(BuildConfig.SERVER_URL, this);

        Picasso.setSingletonInstance(new Picasso.Builder(this)
                .downloader(new OkHttp3Downloader(new OkHttpClient().newBuilder()
                        .addInterceptor(netBridge.getAuthInterceptor())
                        .build()))
                .build()
        );
    }

    public BeaconSearcher getBeaconSearcher() {
        return beaconSearcher;
    }

    public NetBridge getNetBridge() {
        return netBridge;
    }

    public AlgoManager getAlgoManager() {
        return algoManager;
    }
}
