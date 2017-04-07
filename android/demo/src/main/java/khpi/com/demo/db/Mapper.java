package khpi.com.demo.db;

import android.content.ContentValues;
import android.database.Cursor;

import khpi.com.demo.db.DbHelper.Inpoints;
import khpi.com.demo.model.BeaconModel;
import khpi.com.demo.model.Building;
import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;

import java.sql.Date;
import java.util.ArrayList;
import java.util.List;

final class Mapper {

    public static ContentValues getBuildingContentValues(Building building) {
        ContentValues contentValues = new ContentValues();
        contentValues.put(DbHelper.Buildings._ID, building.getId());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_TITLE, building.getTitle());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_SUBTITLE, building.getSubtitle());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_OUTPOINT_ID, building.getOutpointId());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_CREATED_AT, building.getCreated_at().getTime());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_UPDATED_AT, building.getUpdated_at().getTime());
        contentValues.put(DbHelper.Buildings.COLUMN_NAME_POI_NAME, building.getPoiName());

        return contentValues;
    }

    static ContentValues getFloorContentValue(Floor floor){
        ContentValues contentValues = new ContentValues();
        contentValues.put(DbHelper.Floors._ID, floor.getId());
        contentValues.put(DbHelper.Floors.COLUMN_MAP_PATH, floor.getMapPath());
        contentValues.put(DbHelper.Floors.COLUMN_MAP_GRAPH_PATH, floor.getGraphPath());
        contentValues.put(DbHelper.Floors.COLUMN_MASK_PATH, floor.getMaskPath());
        contentValues.put(DbHelper.Floors.COLUMN_BUILDING_ID, floor.getBuildingId());
        contentValues.put(DbHelper.Floors.COLUMN_BUILDING_TITLE, floor.getBuildingTitle());
        contentValues.put(DbHelper.Floors.COLUMN_NUMBER, floor.getNumber());
        contentValues.put(DbHelper.Floors.COLUMN_SUBTITLE, floor.getSubtitle());
        contentValues.put(DbHelper.Floors.COLUMN_WIDTH, floor.getWidth());
        contentValues.put(DbHelper.Floors.COLUMN_HEIGHT, floor.getHeight());
        contentValues.put(DbHelper.Floors.COLUMN_PIXEL_SIZE, floor.getPixelSize());
        return contentValues;
    }

    static List<Building> buildings(Cursor cursor) {
        List<Building> buildings = new ArrayList<>();

        int idIndex = cursor.getColumnIndex(DbHelper.Buildings._ID);
        int titleIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_TITLE);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_SUBTITLE);
        int outpoint_idIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_OUTPOINT_ID);
        int created_atIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_CREATED_AT);
        int updated_atIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_UPDATED_AT);
        int poiNameIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_POI_NAME);

        if (!cursor.moveToFirst()) {
            return buildings;
        }

        do {
            Building building = new Building();
            building.setId(cursor.getInt(idIndex));
            building.setTitle(cursor.getString(titleIndex));
            building.setSubtitle(cursor.getString(subtitleIndex));
            building.setOutpointId(cursor.getInt(outpoint_idIndex));
            building.setCreated_at(new Date(cursor.getLong(created_atIndex)));
            building.setUpdated_at(new Date(cursor.getLong(updated_atIndex)));
            building.setPoiName(cursor.getString(poiNameIndex));

            buildings.add(building);
        } while (cursor.moveToNext());
        cursor.close();
        return buildings;
    }

    static Building cursorToBuilding(Cursor cursor) {
        Building building = new Building();

        if (!cursor.moveToFirst()) {
            return null;
        }

        int idIndex = cursor.getColumnIndex(DbHelper.Buildings._ID);
        int titleIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_TITLE);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_SUBTITLE);
        int outpoint_idIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_OUTPOINT_ID);
        int created_atIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_CREATED_AT);
        int updated_atIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_UPDATED_AT);
        int poiNameIndex = cursor.getColumnIndex(DbHelper.Buildings.COLUMN_NAME_POI_NAME);

        building.setId(cursor.getLong(idIndex));
        building.setTitle(cursor.getString(titleIndex));
        building.setSubtitle(cursor.getString(subtitleIndex));
        building.setOutpointId(cursor.getLong(outpoint_idIndex));
        building.setCreated_at(new Date(cursor.getLong(created_atIndex)));
        building.setUpdated_at(new Date(cursor.getLong(updated_atIndex)));
        building.setPoiName(cursor.getString(poiNameIndex));

        cursor.close();
        return building;
    }

    static BeaconModel cursorToBeaconModel(Cursor cursor){
        BeaconModel beaconModel = new BeaconModel();

        if(!cursor.moveToFirst()){
            return null;
        }

        int xIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_X);
        int yIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_Y);
        int zIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_Z);
        int macAddressIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MAC_ADDRESS);
        int majorIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MAJOR);
        int minorIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MINOR);
        int dampIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_DAMP);
        int floorIdIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_FLOOR_ID);
        int floorNumberIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_FLOOR_NUMBER);
        int buildingIdIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_BUILDING_ID);
        int buildingTitleIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_BUILDING_TITLE);
        int uuidIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_UUID);
        int txPowerIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_TXPOWER);

        beaconModel.setPositionX(cursor.getFloat(xIndex));
        beaconModel.setPositionY(cursor.getFloat(yIndex));
        beaconModel.setPositionZ(cursor.getFloat(zIndex));
        beaconModel.setMacAddress(cursor.getString(macAddressIndex));
        beaconModel.setMajor(cursor.getInt(majorIndex));
        beaconModel.setMinor(cursor.getInt(minorIndex));
        beaconModel.setDamp(cursor.getFloat(dampIndex));
        beaconModel.setFloorId(cursor.getInt(floorIdIndex));
        beaconModel.setFloorNumber(cursor.getInt(floorNumberIndex));
        beaconModel.setBuildingId(cursor.getInt(buildingIdIndex));
        beaconModel.setBuildingTitle(cursor.getString(buildingTitleIndex));
        beaconModel.setTxpower(cursor.getFloat(txPowerIndex));
        beaconModel.setUuid(cursor.getString(uuidIndex));
        cursor.close();
        return beaconModel;
    }

    static ContentValues getBeaconContentValues(BeaconModel beaconModel){
        ContentValues cv = new ContentValues();
        cv.put(DbHelper.Beacons.COLUMN_NAME_X, beaconModel.getPositionX());
        cv.put(DbHelper.Beacons.COLUMN_NAME_Y, beaconModel.getPositionY());
        cv.put(DbHelper.Beacons.COLUMN_NAME_Z, beaconModel.getPositionZ());
        cv.put(DbHelper.Beacons.COLUMN_NAME_MAC_ADDRESS, beaconModel.getMacAddress());
        cv.put(DbHelper.Beacons.COLUMN_NAME_MAJOR, beaconModel.getMajor());
        cv.put(DbHelper.Beacons.COLUMN_NAME_MINOR, beaconModel.getMinor());
        cv.put(DbHelper.Beacons.COLUMN_NAME_DAMP, beaconModel.getDamp());
        cv.put(DbHelper.Beacons.COLUMN_NAME_FLOOR_ID, beaconModel.getFloorId());
        cv.put(DbHelper.Beacons.COLUMN_NAME_FLOOR_NUMBER, beaconModel.getFloorNumber());
        cv.put(DbHelper.Beacons.COLUMN_NAME_BUILDING_ID, beaconModel.getBuildingId());
        cv.put(DbHelper.Beacons.COLUMN_NAME_BUILDING_TITLE, beaconModel.getBuildingTitle());
        cv.put(DbHelper.Beacons.COLUMN_NAME_UUID, beaconModel.getUuid());
        cv.put(DbHelper.Beacons.COLUMN_NAME_TXPOWER, beaconModel.getTxpower());
        return cv;
    }

    static List<BeaconModel> beacons(Cursor cursor){
        List<BeaconModel> beaconModelList = new ArrayList<>();

        int xIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_X);
        int yIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_Y);
        int zIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_Z);
        int macAddressIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MAC_ADDRESS);
        int majorIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MAJOR);
        int minorIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_MINOR);
        int dampIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_DAMP);
        int floorIdIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_FLOOR_ID);
        int floorNumberIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_FLOOR_NUMBER);
        int buildingIdIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_BUILDING_ID);
        int buildingTitleIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_BUILDING_TITLE);
        int uuidIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_UUID);
        int txPowerIndex = cursor.getColumnIndex(DbHelper.Beacons.COLUMN_NAME_TXPOWER);

        if(!cursor.moveToFirst()){
            return beaconModelList;
        }

        do {
            BeaconModel beaconModel = new BeaconModel();
            beaconModel.setPositionX(cursor.getFloat(xIndex));
            beaconModel.setPositionY(cursor.getFloat(yIndex));
            beaconModel.setPositionZ(cursor.getFloat(zIndex));
            beaconModel.setMacAddress(cursor.getString(macAddressIndex));
            beaconModel.setMajor(cursor.getInt(majorIndex));
            beaconModel.setMinor(cursor.getInt(minorIndex));
            beaconModel.setDamp(cursor.getFloat(dampIndex));
            beaconModel.setFloorId(cursor.getInt(floorIdIndex));
            beaconModel.setFloorNumber(cursor.getInt(floorNumberIndex));
            beaconModel.setBuildingId(cursor.getInt(buildingIdIndex));
            beaconModel.setBuildingTitle(cursor.getString(buildingTitleIndex));
            beaconModel.setTxpower(cursor.getFloat(txPowerIndex));
            beaconModel.setUuid(cursor.getString(uuidIndex));
            beaconModelList.add(beaconModel);
        }while (cursor.moveToNext());
        cursor.close();
        return beaconModelList;
    }

    static List<Floor> floors(Cursor cursor){
        List<Floor> floorList = new ArrayList<>();
        int idIndex = cursor.getColumnIndex(DbHelper.Floors._ID);
        int mapPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MAP_PATH);
        int graphPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MAP_GRAPH_PATH);
        int maskPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MASK_PATH);
        int indoorBuildingIdIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_BUILDING_ID);
        int indoorBuildingTitleIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_BUILDING_TITLE);
        int numberIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_NUMBER);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_SUBTITLE);
        int widthIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_WIDTH);
        int heightIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_HEIGHT);
        int pixelSizeIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_PIXEL_SIZE);
        int configPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_CONFIG_PATH);

        if(!cursor.moveToFirst()){return floorList;}

        do {
            Floor floorModel = new Floor();
            floorModel.setId(cursor.getInt(idIndex));
            floorModel.setMapPath(cursor.getString(mapPathIndex));
            floorModel.setGraphPath(cursor.getString(graphPathIndex));
            floorModel.setMaskPath(cursor.getString(maskPathIndex));
            floorModel.setBuildingId(cursor.getInt(indoorBuildingIdIndex));
            floorModel.setBuildingTitle(cursor.getString(indoorBuildingTitleIndex));
            floorModel.setNumber(cursor.getInt(numberIndex));
            floorModel.setWidth(cursor.getDouble(widthIndex));
            floorModel.setSubtitle(cursor.getString(subtitleIndex));
            floorModel.setHeight(cursor.getDouble(heightIndex));
            floorModel.setPixelSize(cursor.getDouble(pixelSizeIndex));
            floorModel.setConfigPath(cursor.getString(configPathIndex));
            floorList.add(floorModel);
        }while(cursor.moveToNext());
        cursor.close();
        return  floorList;
    }

    static Floor cursorToFloor(Cursor cursor){
        Floor floor = new Floor();
        int idIndex = cursor.getColumnIndex(DbHelper.Floors._ID);
        int mapPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MAP_PATH);
        int graphPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MAP_GRAPH_PATH);
        int maskPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_MASK_PATH);
        int indoorBuildingIdIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_BUILDING_ID);
        int indoorBuildingTitleIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_BUILDING_TITLE);
        int numberIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_NUMBER);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_SUBTITLE);
        int widthIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_WIDTH);
        int heightIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_HEIGHT);
        int pixelSizeIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_PIXEL_SIZE);
        int configPathIndex = cursor.getColumnIndex(DbHelper.Floors.COLUMN_CONFIG_PATH);

        if(!cursor.moveToFirst()){return null;}
        floor.setId(cursor.getInt(idIndex));
        floor.setMapPath(cursor.getString(mapPathIndex));
        floor.setGraphPath(cursor.getString(graphPathIndex));
        floor.setMaskPath(cursor.getString(maskPathIndex));
        floor.setBuildingId(cursor.getInt(indoorBuildingIdIndex));
        floor.setBuildingTitle(cursor.getString(indoorBuildingTitleIndex));
        floor.setNumber(cursor.getInt(numberIndex));

        floor.setWidth(cursor.getDouble(widthIndex));
        floor.setSubtitle(cursor.getString(subtitleIndex));
        floor.setHeight(cursor.getDouble(heightIndex));
        floor.setPixelSize(cursor.getDouble(pixelSizeIndex));
        floor.setConfigPath(cursor.getString(configPathIndex));
        cursor.close();
        return floor;
    }

    public static ContentValues getInpointContentValues(Inpoint point) {
        ContentValues contentValues = new ContentValues();
        contentValues.put(Inpoints._ID, point.getId());
        contentValues.put(Inpoints.COLUMN_NAME_FLOOR_ID, point.getFloorId());
        contentValues.put(Inpoints.COLUMN_NAME_TITLE, point.getTitle());
        contentValues.put(Inpoints.COLUMN_NAME_SUBTITLE, point.getSubtitle());
        contentValues.put(Inpoints.COLUMN_NAME_DESCRIPTION, point.getDescription());
        contentValues.put(Inpoints.COLUMN_NAME_IMAGE, point.getImage());
        contentValues.put(Inpoints.COLUMN_NAME_HINT, point.getHint());
        contentValues.put(Inpoints.COLUMN_NAME_TAGS, point.getTags());
        contentValues.put(Inpoints.COLUMN_NAME_TYPE, point.getType());
        contentValues.put(Inpoints.COLUMN_NAME_ICON_ID, point.getIcon_id());
        contentValues.put(Inpoints.COLUMN_NAME_X, point.getX());
        contentValues.put(Inpoints.COLUMN_NAME_Y, point.getY());
        contentValues.put(Inpoints.COLUMN_NAME_NEAR_ROUTE_X, point.getNear_route_x());
        contentValues.put(Inpoints.COLUMN_NAME_NEAR_ROUTE_Y, point.getNear_route_y());
        contentValues.put(Inpoints.COLUMN_NAME_GPS_LAT, point.getGps_lat());
        contentValues.put(Inpoints.COLUMN_NAME_GPS_LON, point.getGps_lon());
        contentValues.put(Inpoints.COLUMN_NAME_GPS_ALT, point.getGps_alt());
        contentValues.put(Inpoints.COLUMN_NAME_BUILDING_ID, point.getMap_id());
        contentValues.put(Inpoints.COLUMN_NAME_CREATED_AT, point.getCreated_at().getTime());
        contentValues.put(Inpoints.COLUMN_NAME_UPDATED_AT, point.getUpdated_at().getTime());
        contentValues.put(Inpoints.COLUMN_NAME_FLOOR_NUMBER, point.getFloorNumber());
        contentValues.put(Inpoints.COLUMN_NAME_BUILDING_ID, point.getBuildingId());
        contentValues.put(Inpoints.COLUMN_NAME_BUILDING_TITLE, point.getBuildingTitle());

        return contentValues;
    }

    static List<Inpoint> inpoints(Cursor cursor) {
        List<Inpoint> points = new ArrayList<>();

        int idIndex = cursor.getColumnIndex(DbHelper.Inpoints._ID);
        int floorIdIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_FLOOR_ID);
        int titleIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TITLE);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_SUBTITLE);
        int descriptionIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_DESCRIPTION);
        int imageIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_IMAGE);
        int hintIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_HINT);
        int tagsIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TAGS);
        int typeIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TYPE);
        int icon_idIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_ICON_ID);
        int xIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_X);
        int yIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_Y);
        int near_route_xIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_NEAR_ROUTE_X);
        int near_route_yIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_NEAR_ROUTE_Y);
        int gps_latIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_LAT);
        int gps_lonIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_LON);
        int gps_altIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_ALT);
        int map_idIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_ID);
        int created_atIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_CREATED_AT);
        int updated_atIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_UPDATED_AT);
        int floorNumberIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_FLOOR_NUMBER);
        int buildingIdIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_ID);
        int buildingTitleIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_TITLE);


        if (!cursor.moveToFirst()) {
            return points;
        }

        do {
            Inpoint point = new Inpoint();

            point.setId(cursor.getLong(idIndex));
            point.setFloorId(cursor.getLong(floorIdIndex));
            point.setTitle(cursor.getString(titleIndex));
            point.setSubtitle(cursor.getString(subtitleIndex));
            point.setDescription(cursor.getString(descriptionIndex));
            point.setImage(cursor.getString(imageIndex));
            point.setHint(cursor.getString(hintIndex));
            point.setTags(cursor.getString(tagsIndex));
            point.setType(cursor.getString(typeIndex));
            point.setIcon_id(cursor.getString(icon_idIndex));
            point.setX(cursor.getDouble(xIndex));
            point.setY(cursor.getDouble(yIndex));
            point.setNear_route_x(cursor.getDouble(near_route_xIndex));
            point.setNear_route_y(cursor.getDouble(near_route_yIndex));
            point.setGps_lat(cursor.getDouble(gps_latIndex));
            point.setGps_lon(cursor.getDouble(gps_lonIndex));
            point.setGps_alt(cursor.getDouble(gps_altIndex));
            point.setMap_id(cursor.getLong(map_idIndex));
            point.setCreated_at(new Date(cursor.getLong(created_atIndex)));
            point.setUpdated_at(new Date(cursor.getLong(updated_atIndex)));
            point.setFloorNumber(cursor.getInt(floorNumberIndex));
            point.setBuildingId(cursor.getInt(buildingIdIndex));
            point.setBuildingTitle(cursor.getString(buildingTitleIndex));

            points.add(point);
        } while (cursor.moveToNext());
        cursor.close();
        return points;
    }

    static List<Integer> inpointsId(Cursor cursor) {
        List<Integer> points = new ArrayList<>();

        int idIndex = cursor.getColumnIndex(DbHelper.Inpoints._ID);

        if (!cursor.moveToFirst()) {
            return points;
        }

        do {
            points.add(cursor.getInt(idIndex));
        } while (cursor.moveToNext());
        cursor.close();
        return points;
    }


    static Inpoint inpoint(Cursor cursor) {
        if (!cursor.moveToFirst()) {
            return null;
        }

        int idIndex = cursor.getColumnIndex(DbHelper.Inpoints._ID);
        int floorIdIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_FLOOR_ID);
        int titleIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TITLE);
        int subtitleIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_SUBTITLE);
        int descriptionIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_DESCRIPTION);
        int imageIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_IMAGE);
        int hintIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_HINT);
        int tagsIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TAGS);
        int typeIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_TYPE);
        int icon_idIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_ICON_ID);
        int xIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_X);
        int yIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_Y);
        int near_route_xIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_NEAR_ROUTE_X);
        int near_route_yIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_NEAR_ROUTE_Y);
        int gps_latIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_LAT);
        int gps_lonIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_LON);
        int gps_altIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_GPS_ALT);
        int map_idIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_ID);
        int created_atIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_CREATED_AT);
        int updated_atIndex = cursor.getColumnIndex(DbHelper.Inpoints.COLUMN_NAME_UPDATED_AT);
        int floorNumberIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_FLOOR_NUMBER);
        int buildingIdIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_ID);
        int buildingTitleIndex = cursor.getColumnIndex(Inpoints.COLUMN_NAME_BUILDING_TITLE);


        Inpoint point = new Inpoint();

        point.setId(cursor.getLong(idIndex));
        point.setFloorId(cursor.getLong(floorIdIndex));
        point.setTitle(cursor.getString(titleIndex));
        point.setSubtitle(cursor.getString(subtitleIndex));
        point.setDescription(cursor.getString(descriptionIndex));
        point.setImage(cursor.getString(imageIndex));
        point.setHint(cursor.getString(hintIndex));
        point.setTags(cursor.getString(tagsIndex));
        point.setType(cursor.getString(typeIndex));
        point.setIcon_id(cursor.getString(icon_idIndex));
        point.setX(cursor.getDouble(xIndex));
        point.setY(cursor.getDouble(yIndex));
        point.setNear_route_x(cursor.getDouble(near_route_xIndex));
        point.setNear_route_y(cursor.getDouble(near_route_yIndex));
        point.setGps_lat(cursor.getDouble(gps_latIndex));
        point.setGps_lon(cursor.getDouble(gps_lonIndex));
        point.setGps_alt(cursor.getDouble(gps_altIndex));
        point.setMap_id(cursor.getLong(map_idIndex));
        point.setCreated_at(new Date(cursor.getLong(created_atIndex)));
        point.setUpdated_at(new Date(cursor.getLong(updated_atIndex)));
        point.setFloorNumber(cursor.getInt(floorNumberIndex));
        point.setBuildingId(cursor.getInt(buildingIdIndex));
        point.setBuildingTitle(cursor.getString(buildingTitleIndex));
        cursor.close();
        return point;
    }
}
