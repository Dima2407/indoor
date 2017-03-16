package khpi.com.demo.net.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;
import khpi.com.demo.model.Building;

import java.util.List;

public class BuildingList {

    @SerializedName("data")
    @Expose
    private List<Building> data;

    public BuildingList(){}

    public List<Building> getData() {
        return data;
    }

    public void setData(List<Building> data) {
        this.data = data;
    }



}

