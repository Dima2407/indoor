package khpi.com.demo.ui.adapter;

import android.os.Handler;
import android.os.Looper;
import android.support.annotation.IdRes;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

/**
 * Created by ivan.k on 04.07.2016.
 */
public abstract class AbstractRecyclerAdapter<T> extends RecyclerView.Adapter<AbstractRecyclerAdapter.BaseViewHolder> implements View.OnClickListener,View.OnLongClickListener {

    protected List<T> data;
    protected LayoutInflater layoutInflater;
    protected Handler uiHandler;
    private OnClickListener<T> clickListener;
    private OnLongClickListener<T> longClickListener;
    private Runnable notifyInUiThread = new Runnable() {
        @Override
        public void run() {
            notifyDataSetChanged();
        }
    };

    public AbstractRecyclerAdapter() {
        this.data = new ArrayList<>();
        uiHandler = new Handler(Looper.getMainLooper());
    }


    @Override
    public final BaseViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        if(layoutInflater==null){
            layoutInflater = LayoutInflater.from(parent.getContext());
        }
        BaseViewHolder vh = onCreateViewHolder(layoutInflater, parent, viewType);
        vh.itemView.setOnClickListener(this);
        vh.itemView.setOnLongClickListener(this);
        vh.setInternalClickers(this,this);
        return vh;
    }

    protected abstract BaseViewHolder onCreateViewHolder(LayoutInflater layoutInflater, ViewGroup parent, int viewType);

    @Override
    public void onBindViewHolder(BaseViewHolder holder, int position, List<Object> payloads) {
        holder.itemView.setTag(position);
        holder.fillI(data.get(position),position);
    }

    @Override
    public void onBindViewHolder(BaseViewHolder holder, int position) {
        holder.itemView.setTag(position);
        holder.fillI(data.get(position),position);
    }

    @Override
    public int getItemCount() {
        return data.size();
    }

    public void addItem(T t){
        data.add(t);
        uiHandler.post(notifyInUiThread);
    }

    public void addItems(Collection<T> items){
        data.addAll(items);
        uiHandler.post(notifyInUiThread);
    }

    public void addItems(T... items){
        for (T item : items) {
            data.add(item);
        }
        uiHandler.post(notifyInUiThread);
    }


    public void setClickListener(OnClickListener<T> clickListener) {
        this.clickListener = clickListener;
    }

    public void setLongClickListener(OnLongClickListener<T> longClickListener) {
        this.longClickListener = longClickListener;
    }

    @Override
    public void onClick(View v) {
        int position = (int) v.getTag();
        if (clickListener!=null) {
            clickListener.onClick(v,data.get(position),position);
        }
    }

    @Override
    public boolean onLongClick(View v) {
        int position = (int) v.getTag();
        if (longClickListener!=null) {
            longClickListener.onClick(v,data.get(position),position);
            return true;
        }
        return false;
    }

    public void clear() {
        data.clear();
        uiHandler.post(notifyInUiThread);
    }

    public static abstract class BaseViewHolder<T> extends RecyclerView.ViewHolder {

        public BaseViewHolder(View itemView) {
            super(itemView);
        }

        protected View findViewById(@IdRes int id){
            return itemView.findViewById(id);
        }

        public void setInternalClickers(View.OnClickListener clicker, View.OnLongClickListener longClicker){
        }

        private void fillI(T t, int position){
            itemView.setTag(position);
            fill(t,position);

        }
        public abstract void fill(T t, int position);


    }

    public interface OnClickListener<T> {
        void onClick(View v, T item, int position);
    }
    public interface OnLongClickListener<T> {
        void onClick(View v, T item, int position);
    }

}
