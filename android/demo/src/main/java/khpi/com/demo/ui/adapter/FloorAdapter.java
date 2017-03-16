package khpi.com.demo.ui.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import khpi.com.demo.R;
import khpi.com.demo.model.Floor;

public class FloorAdapter extends AbstractRecyclerAdapter<Floor> {
    @Override
    protected BaseViewHolder onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType) {
        return new FloorAdapter.VH(layoutInflater.inflate(R.layout.item_indoor_view, parent,false));
    }

    public class VH extends AbstractRecyclerAdapter.BaseViewHolder<Floor> {

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
        public void fill(Floor map, int position) {
            title.setText(map.getSubtitle());
            subtitle.setText(map.getSubtitle());
        }
    }
}
