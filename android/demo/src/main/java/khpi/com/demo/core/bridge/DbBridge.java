package khpi.com.demo.core.bridge;

import khpi.com.demo.model.Building;
import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.routing.FloorModel;

import java.util.List;
import java.util.Observer;

public interface DbBridge {

    String BUILDINGS_UPDATED = "indoor maps updated";
    String INPOINTS_UPDATED = "inpoints updated";
    String FLOORS_UPDATED = "floor updated";

    String NEW_ROUTE = "new route";

    void addObserver(Observer observer);

    void deleteObserver(Observer observer);

    List<Building> getBuildings();

    List<Floor> getFloorsByBuildingId(long id);

    List<Building> getBuildingsByOutpointId(long id);

    void saveRoute(Route steps);

    Route getRoute();

    FloorModel getIndoorMap();

    void setDestinationPoint(Point point);

    Point getDestinationPoint();

    void saveBuildings(List<Building> body);

    void saveInpoinrs(List<Inpoint> body);

    List<Inpoint> getInpoints();

    List<Inpoint> getInpointsByBuildingAndFloorId(long id, int floorId);
    List<Inpoint> getInpointByFloorId(long id);
    void saveFloors(List<Floor> floors);

    Inpoint getInpointById(int id);

}
