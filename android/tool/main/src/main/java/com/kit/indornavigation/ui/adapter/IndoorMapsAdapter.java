package com.kit.indornavigation.ui.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.github.alwayswannasleep.models.IndoorMap;
import com.kit.indornavigation.R;

import butterknife.Bind;
import butterknife.ButterKnife;

public class IndoorMapsAdapter extends AbstractRecyclerAdapter<IndoorMap> {

    @Override
    protected VH onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType) {
        return new VH(layoutInflater.inflate(R.layout.item_floor, parent, false));
    }

    static class VH extends AbstractRecyclerAdapter.BaseViewHolder<IndoorMap> {

        @Bind(R.id.floor_name)
        TextView floorName;
        @Bind(R.id.floor_description)
        TextView floorDesc;

        VH(View itemView) {
            super(itemView);
            ButterKnife.bind(this, itemView);
        }

        @Override
        public void fill(IndoorMap floorMap, int position) {
            floorName.setText(floorMap.getTitle());
            floorDesc.setText(floorMap.getSubTitle());
        }
    }
}
