package com.kit.indornavigation.ui.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.github.alwayswannasleep.models.FloorModel;
import com.kit.indornavigation.R;
import com.kit.indornavigation.model.IndoorMap;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.Collection;

import butterknife.Bind;

public class MapsAdapter extends AbstractRecyclerAdapter<IndoorMap> {

    private OptionsClicker clicker;

    private View.OnClickListener onClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            IndoorMap map = (IndoorMap) v.getTag();
            if (clicker != null) {
                clicker.onOptionsClicked(map, v);
            }
        }
    };

    @Override
    protected BaseViewHolder<IndoorMap> onCreateViewHolder(final LayoutInflater layoutInflater, final ViewGroup parent, final int viewType) {
        return new VH(LayoutInflater.from(parent.getContext()).inflate(R.layout.item_map, parent, false));
    }

    public void setData(Collection<IndoorMap> collection) {
        data = new ArrayList<>(collection);
        notifyDataSetChanged();
    }

    public void setClicker(OptionsClicker clicker) {
        this.clicker = clicker;
    }

    class VH extends BaseViewHolder<IndoorMap> {

        @Bind(R.id.im_image)
        ImageView image;

        @Bind(R.id.map_name)
        TextView mapName;

        @Bind(R.id.map_size)
        TextView mapSize;

        @Bind(R.id.beacons_size)
        TextView beaconsSize;

        VH(View itemView) {
            super(itemView);
        }

        @Override
        public void fill(final IndoorMap indoorMap, final int position) {
            mapName.setText(indoorMap.getName());
            mapSize.setText(indoorMap.getFloors().size() + " floors");
            int a =0;
            for (FloorModel floorModel : indoorMap.getFloors()) {
                a+=floorModel.getBeacons().size();
            }
            beaconsSize.setText("beacons count: " + a);

            Picasso.with(image.getContext())
                    .load(indoorMap.getFloors().get(0).getImgPath())
                    .centerInside()
                    .resizeDimen(R.dimen.item_map_image_width, R.dimen.item_map_image_height)
                    .placeholder(R.mipmap.ic_launcher)
                    .into(image);
        }
    }

    public interface OptionsClicker {
        void onOptionsClicked(IndoorMap map, View v);
    }
}
