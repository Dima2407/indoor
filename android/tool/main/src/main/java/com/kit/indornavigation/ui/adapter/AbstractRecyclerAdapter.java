package com.kit.indornavigation.ui.adapter;

import android.os.Handler;
import android.os.Looper;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public abstract class AbstractRecyclerAdapter<T> extends RecyclerView.Adapter<AbstractRecyclerAdapter.BaseViewHolder<T>> {

    protected List<T> data;
    private LayoutInflater layoutInflater;
    private Handler uiHandler;
    private OnClickListener<T> clickListener;
    private Runnable notifyInUiThread = new Runnable() {
        @Override
        public void run() {
            notifyDataSetChanged();
        }
    };

    AbstractRecyclerAdapter() {
        this.data = new ArrayList<>();
        uiHandler = new Handler(Looper.getMainLooper());
    }

    @Override
    public final BaseViewHolder<T> onCreateViewHolder(ViewGroup parent, int viewType) {
        if (layoutInflater == null) {
            layoutInflater = LayoutInflater.from(parent.getContext());
        }
        BaseViewHolder<T> vh = onCreateViewHolder(layoutInflater, parent, viewType);
        vh.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                AbstractRecyclerAdapter.this.onClick(view);
            }
        });
        return vh;
    }

    protected abstract BaseViewHolder<T> onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType);

    @Override
    public void onBindViewHolder(BaseViewHolder<T> holder, int position, List<Object> payloads) {
        holder.itemView.setTag(position);
        holder.fill(data.get(position), position);
    }

    @Override
    public void onBindViewHolder(BaseViewHolder<T> holder, int position) {
        holder.itemView.setTag(position);
        holder.fill(data.get(position), position);
    }

    @Override
    public int getItemCount() {
        return data.size();
    }

    public void setItems(Collection<T> items) {
        data.clear();

        if (items != null) {
            data.addAll(items);
        }

        uiHandler.post(notifyInUiThread);
    }

    public void setClickListener(OnClickListener<T> clickListener) {
        this.clickListener = clickListener;
    }

    public void onClick(View v) {
        int position = (int) v.getTag();
        if (clickListener != null) {
            clickListener.onClick(v, data.get(position), position);
        }
    }

    public void clear() {
        data.clear();
        uiHandler.post(notifyInUiThread);
    }

    static abstract class BaseViewHolder<T> extends RecyclerView.ViewHolder {

        BaseViewHolder(View itemView) {
            super(itemView);
        }

        public abstract void fill(T t, int position);
    }

    public interface OnClickListener<T> {

        void onClick(View v, T item, int position);
    }
}
