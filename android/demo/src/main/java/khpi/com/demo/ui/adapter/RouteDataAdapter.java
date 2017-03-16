package khpi.com.demo.ui.adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import khpi.com.demo.R;
import khpi.com.demo.model.Step;
import khpi.com.demo.utils.ManeuverHelper;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

public final class RouteDataAdapter extends RecyclerView.Adapter<RouteDataAdapter.ViewHolder> {

    private Picasso picasso;
    private LayoutInflater layoutInflater;
    private List<Step> routeData;

    public RouteDataAdapter(Context context) {
        picasso = Picasso.with(context);
        layoutInflater = LayoutInflater.from(context);

        routeData = new ArrayList<>();
        setHasStableIds(false);
    }

    @Override
    public int getItemViewType(final int position) {
        int viewType = R.layout.route_data_item_view;

        if (position == 0) {
            viewType = R.layout.route_data_item_header;
        } else if (position == getItemCount() - 1) {
            viewType = R.layout.route_data_item_footer;
        } else if (position % 2 != 0) {
            viewType = R.layout.route_data_item_delimeter;
        }

        return viewType;
    }

    @Override
    public ViewHolder onCreateViewHolder(final ViewGroup parent, final int viewType) {
        View view = layoutInflater.inflate(viewType, parent, false);

        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(final ViewHolder holder, final int position) {
        if (holder.maneuverIcon == null && holder.textHint == null) {
            return;
        }

        Step step = routeData.get(position);

        int icon;

        if (step.getManeuver() == null) {
            icon = R.drawable.map_icn;
        } else {
            icon = ManeuverHelper.getManeuverIcon(step.getManeuver());
        }

        String duration;

        if (step.getDuration() == null) {
            duration = "";
        } else {
            duration = " (" + step.getDuration() + ")";
        }

        String hint = step.getHint().trim();
        hint = hint.replaceAll("\\n.*", "");

        String result = hint + duration;
        holder.textHint.setText(result);

        if (holder.maneuverIcon != null) {
            picasso.load(icon).into(holder.maneuverIcon);
        }
    }

    @Override
    public int getItemCount() {
        return routeData.size();
    }

    public void putData(List<Step> steps) {
        steps = new ArrayList<>(steps);

        for (int i = 1; i < steps.size(); i += 2) {
            steps.add(i, new Step());
        }

        if (routeData == null) {
            routeData = steps;
        } else {
            routeData.clear();
            routeData.addAll(steps);
        }

        notifyDataSetChanged();
    }

    static final class ViewHolder extends RecyclerView.ViewHolder {

        ImageView maneuverIcon;
        TextView textHint;

        ViewHolder(final View itemView) {
            super(itemView);

            maneuverIcon = (ImageView) itemView.findViewById(R.id.route_item_maneuver_icon);
            textHint = (TextView) itemView.findViewById(R.id.route_item_hint);
        }
    }
}
