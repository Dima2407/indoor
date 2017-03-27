package com.kit.indornavigation.model;

import com.github.alwayswannasleep.models.FloorModel;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 * Created by kit on 9/4/16.
 */
public class IndoorMap {

    String name;
    String submane;
    String serverId;
    String localId;
    List<FloorModel> floors;

    public IndoorMap() {
        name = "";
        submane  ="";
        floors = new ArrayList<>();
        localId = UUID.randomUUID().toString();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSubmane() {
        return submane;
    }

    public void setSubmane(String submane) {
        this.submane = submane;
    }

    public List<FloorModel> getFloors() {
        return floors;
    }

    public void setFloors(List<FloorModel> floors) {
        this.floors = floors;
    }

    public String getMapUid() {
        return serverId!=null?serverId:localId;
    }
}
