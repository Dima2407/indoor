package khpi.com.demo.ui.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import khpi.com.demo.R;
import khpi.com.demo.model.Building;


public class BuildingAdapter extends AbstractRecyclerAdapter<Building> {
    @Override
    protected BaseViewHolder onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType) {
        return new VH(layoutInflater.inflate(R.layout.item_indoor_view, parent,false));
    }

    public class VH extends AbstractRecyclerAdapter.BaseViewHolder<Building> {

        private TextView title;
        private TextView subtitle;
        private TextView metadata;

        public VH(View itemView) {
            super(itemView);
            title = (TextView) findViewById(R.id.title);
            subtitle = (TextView) findViewById(R.id.subtitle);
            title = (TextView) findViewById(R.id.title);
        }

        @Override
        public void fill(Building map, int position) {
            title.setText(map.getTitle());
            subtitle.setText(map.getSubtitle());
        }
    }
}
