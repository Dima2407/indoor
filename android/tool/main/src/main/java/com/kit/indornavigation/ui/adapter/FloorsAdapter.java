package com.kit.indornavigation.ui.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.github.alwayswannasleep.models.FloorModel;
import com.kit.indornavigation.R;

import butterknife.Bind;
import butterknife.ButterKnife;

public class FloorsAdapter extends AbstractRecyclerAdapter<FloorModel> {

    @Override
    protected VH onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType) {
        return new VH(layoutInflater.inflate(R.layout.item_floor, parent, false));
    }

    static class VH extends AbstractRecyclerAdapter.BaseViewHolder<FloorModel> {

        @Bind(R.id.floor_name)
        TextView floorName;
        @Bind(R.id.floor_description)
        TextView floorDesc;

        VH(View itemView) {
            super(itemView);
            ButterKnife.bind(this, itemView);
        }

        @Override
        public void fill(FloorModel floorMap, int position) {
            floorName.setText(floorMap.getBuildingTitle());
            floorDesc.setText(floorMap.getSubtitle());
        }
    }
}
