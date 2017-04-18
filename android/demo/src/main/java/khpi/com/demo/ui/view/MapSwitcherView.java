package khpi.com.demo.ui.view;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

import khpi.com.demo.R;
import khpi.com.demo.model.Floor;

import java.util.ArrayList;
import java.util.List;


public class MapSwitcherView extends RelativeLayout implements View.OnClickListener {

    LinearLayout floors;
    boolean open = false;

    private List<Floor> data = new ArrayList<>();
    private ChangeMapListener listener;

    public MapSwitcherView(Context context) {
        super(context);
        init();
    }

    public MapSwitcherView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    public MapSwitcherView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init();
    }

    @Override
    protected void onLayout(boolean b, int i, int i1, int i2, int i3) {
        super.onLayout(b,i,i1,i2,i3);
    }

    private void init() {

        inflate(getContext(), R.layout.view_map_switcher_root,this);
        floors = (LinearLayout) findViewById(R.id.floor_container);

        floors.setVisibility((open) ? View.VISIBLE : View.GONE);


        LayoutInflater lf = LayoutInflater.from(getContext());
        int pos = 0;
        for (Floor flor : data) {
            View v =  lf.inflate(R.layout.item_view_floor, null, false);
            TextView tv = (TextView) v.findViewById(R.id.text);
            tv.setText(flor.getSubtitle());
            tv.setTag(pos);
            tv.setOnClickListener(this);
            floors.addView(v);
            pos++;
        }
    }

    public void setMap(List<Floor> maps){
        data.clear();
        data.addAll(maps);
        LayoutInflater lf = LayoutInflater.from(getContext());
        int pos = 1;
        for (Floor flor : data) {
            View v =  lf.inflate(R.layout.item_view_floor, null, false);
            TextView tv = (TextView) v.findViewById(R.id.text);
            tv.setText(flor.getSubtitle());
            tv.setTag(pos);
            tv.setOnClickListener(this);
            floors.addView(v);
            pos++;
        }
    }

    @Override
    public void onClick(View view) {
        switch (view.getId()){
            default:
                Integer pos = (Integer) view.getTag();
                Log.d("MapSwitcherView", "pos:" + pos);
                listener.onMapSelected();
                open=!open;
                floors.setVisibility((open) ? View.VISIBLE : View.GONE);
                break;
        }
    }

    public void setListener(ChangeMapListener listener) {
        this.listener = listener;
    }

    public interface ChangeMapListener{
        void onMapSelected();
    }

}
