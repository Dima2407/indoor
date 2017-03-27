package khpi.com.demo.db;

import android.content.Context;

import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.model.BeaconModel;
import khpi.com.demo.model.Building;
import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.routing.FloorModel;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;

public final class DbFacade extends Observable implements DbBridge {


    private BuildingRepository buildingRepository;
    private InpointsRepository inpointsRepository;
    private FloorRepository floorRepository;
    private BeaconRepository beaconRepository;
    private Point destinationPoint;
    private Route route;

    public DbFacade(Context context) {
        DbHelper dbHelper = new DbHelper(context);

        buildingRepository = new BuildingRepository(dbHelper);
        inpointsRepository = new InpointsRepository(dbHelper);
        floorRepository = new FloorRepository(dbHelper);
        beaconRepository = new BeaconRepository(dbHelper);
    }

    @Override
    public void saveBuildings(List<Building> body) {

        for(Building building : body) {
            buildingRepository.saveBuilding(building);
            setChanged();
            for(Floor floor : building.getFloors()){
                floorRepository.saveFloor(floor);
                setChanged();
                for (BeaconModel beacon : floor.getBeacons()){
                    beaconRepository.saveBeacon(beacon);
                    setChanged();
                }
                for(Inpoint i : inpointsRepository.getInpointsByFloorId(floor.getId())){
                    inpointsRepository.save(i);
                    setChanged();
                }
                setChanged();
            }
        }
        setChanged();
        notifyObservers(DbBridge.BUILDINGS_UPDATED);
    }

    @Override
    public void setDestinationPoint(Point point) {
        this.destinationPoint = point;
    }

    @Override
    public Point getDestinationPoint() {
        return destinationPoint;
    }
    @Override
    public void saveInpoinrs(List<Inpoint> body) {
        inpointsRepository.saveAll(body);
        setChanged();
        notifyObservers(DbBridge.INPOINTS_UPDATED);
    }

    @Override
    public List<Inpoint> getInpoints() {
        return inpointsRepository.getInpoints();
    }

    @Override
    public List<Inpoint> getInpointsByBuildingAndFloorId(long id, int floorId) {
        return inpointsRepository.getInpointsByBuildingAndFloorId(id, floorId);
    }

    @Override
    public List<Building> getBuildings() {
        List<Building> buildingList = new ArrayList<>();
        List<Floor> floorList = new ArrayList<>();
        for(Building building : buildingRepository.getBuildings()){
            for(Floor floor : floorRepository.getFloorsByBuildingId(building.getId())){

                floor.setBeacons(beaconRepository.getBeaconsByFloorId(floor.getId()));
                floor.setInpointIdList(inpointsRepository.getInpointsIdByFloorId(floor.getId()));
                floorList.add(floor);
            }
            building.setFloors(floorList);
            buildingList.add(building);
        }
        return buildingList;
    }
    @Override
    public List<Building> getBuildingsByOutpointId(long id) {
        return buildingRepository.getBuildingsByOutpointId(id);
    }

    @Override
    public void saveRoute(Route steps) {
        this.route = steps;

        setChanged();
        notifyObservers(DbBridge.NEW_ROUTE);
    }

    @Override
    public Route getRoute() {
        return route;
    }
    @Override
    public FloorModel getIndoorMap(){
        FloorModel m = new FloorModel();
        m.setPixelSize(0.01);
        m.setWidth(1035*0.01);
        m.setHeight(800*0.01);
        return m;
    }

    @Override
    public void saveFloors(List<Floor> floors) {
        floorRepository.saveFloors(floors);
        setChanged();
        notifyObservers(DbBridge.FLOORS_UPDATED);
    }

    @Override
    public Inpoint getInpointById(int id) {
        return inpointsRepository.getInpointById(id);
    }

    @Override
    public List<Floor> getFloorsByBuildingId(long id) {
        List<Floor> floorList = new ArrayList<>();
        List<BeaconModel> beaconModelList = new ArrayList<>();
        for(Floor floor : floorRepository.getFloorsByBuildingId(id)){
            beaconModelList = beaconRepository.getBeaconsByFloorId(floor.getId());
            floor.setInpointIdList(inpointsRepository.getInpointsIdByFloorId(floor.getId()));
            floor.setBeacons(beaconModelList);
            floorList.add(floor);
        }
        return floorList;
    }

    @Override
    public List<Inpoint> getInpointByFloorId(long id) {
        return inpointsRepository.getInpointsByFloorId(id);
    }
}