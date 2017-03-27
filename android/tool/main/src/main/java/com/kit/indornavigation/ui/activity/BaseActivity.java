package com.kit.indornavigation.ui.activity;

import android.os.Bundle;
import android.support.annotation.LayoutRes;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import com.kit.indornavigation.core.App;

import butterknife.ButterKnife;

/**
 * Created by ivan.k on 23.06.2016.
 */
public abstract class BaseActivity extends AppCompatActivity {

    protected App app;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app = (App) getApplicationContext();
        setContentView(getLayResId());
        ButterKnife.bind(this);
    }

    @LayoutRes
    public abstract int getLayResId();
}
