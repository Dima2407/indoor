package khpi.com.demo.ui;

import android.support.design.widget.BottomSheetBehavior;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import khpi.com.demo.R;

public final class BottomSheet {

    private final TextView hintText;
    private final View hintContainer;
    private final ImageView hintIcon;
    private final View bottomViewWrapper;
    private final BottomSheetBehavior bottomSheetBehavior;
    private final RecyclerView dataList;
    private final TextView totalDuration;
    private final TextView totalDistance;
    private final View cancelButton;

    public BottomSheet(View bottomViewWrapper, View layout) {
        this.bottomViewWrapper = bottomViewWrapper;
        bottomSheetBehavior = BottomSheetBehavior.from(bottomViewWrapper);

        totalDistance = (TextView) layout.findViewById(R.id.bottom_sheet_total_distance);
        totalDuration = (TextView) layout.findViewById(R.id.bottom_sheet_total_duration);
        dataList = (RecyclerView) layout.findViewById(R.id.bottom_sheet_list);
        cancelButton = layout.findViewById(R.id.bottom_sheet_cancel_btn);
        hintText = (TextView) layout.findViewById(R.id.hint_text);
        hintContainer = layout.findViewById(R.id.hint_container);
        hintIcon = (ImageView) layout.findViewById(R.id.hint_icon);
    }

    public View getBottomViewWrapper() {
        return bottomViewWrapper;
    }

    public BottomSheetBehavior getBottomSheetBehavior() {
        return bottomSheetBehavior;
    }

    public RecyclerView getDataList() {
        return dataList;
    }

    public TextView getTotalDuration() {
        return totalDuration;
    }

    public TextView getTotalDistance() {
        return totalDistance;
    }

    public View getCancelButton() {
        return cancelButton;
    }

    public TextView getHintText() {
        return hintText;
    }

    public View getHintContainer() {
        return hintContainer;
    }

    public ImageView getHintIcon() {
        return hintIcon;
    }
}
