package khpi.com.demo.net.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import khpi.com.demo.model.Inpoint;

import java.util.List;

public class InpointList {

    @SerializedName("data")
    @Expose
    private List<Inpoint> data;

    public InpointList(){}

    public List<Inpoint> getData() {
        return data;
    }

    public void setData(List<Inpoint> data) {
        this.data = data;
    }
}
