package khpi.com.demo.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.provider.BaseColumns;

final class DbHelper extends SQLiteOpenHelper {

    private static final String DB_NAME = "gps_tracker_db";
    private static final int DB_VERSION = 6;

    private static final String TEXT_TYPE = " TEXT";
    private static final String REAL_TYPE = " REAL";
    private static final String INTEGER_TYPE = " INTEGER";
    private static final String COMA_SEP = ",";

    private static final String BUILDINGS_CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS " + Buildings.TABLE_NAME + " (" +
                    Buildings._ID + INTEGER_TYPE + " PRIMARY KEY," +

                    Buildings.COLUMN_NAME_TITLE + TEXT_TYPE + COMA_SEP +
                    Buildings.COLUMN_NAME_SUBTITLE + TEXT_TYPE + COMA_SEP +
                    //Buildings.COLUMN_NAME_DATA + TEXT_TYPE + COMA_SEP +
                    Buildings.COLUMN_NAME_OUTPOINT_ID + INTEGER_TYPE + COMA_SEP +
                    Buildings.COLUMN_NAME_CREATED_AT + REAL_TYPE + COMA_SEP +
                    Buildings.COLUMN_NAME_UPDATED_AT + REAL_TYPE + COMA_SEP +
                    Buildings.COLUMN_NAME_POI_NAME + TEXT_TYPE +
                    ")";

    private static final String INPOINTS_CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS " + Inpoints.TABLE_NAME + " (" +
                    Inpoints._ID + INTEGER_TYPE + " PRIMARY KEY," +
                    Inpoints.COLUMN_NAME_FLOOR_ID + INTEGER_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_TITLE + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_SUBTITLE + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_DESCRIPTION + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_IMAGE + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_HINT + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_TAGS + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_TYPE + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_ICON_ID + TEXT_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_X + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_Y + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_NEAR_ROUTE_X + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_NEAR_ROUTE_Y + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_GPS_LAT + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_GPS_LON + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_GPS_ALT + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_BUILDING_ID + INTEGER_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_CREATED_AT + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_UPDATED_AT + REAL_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_FLOOR_NUMBER + INTEGER_TYPE + COMA_SEP +
                    Inpoints.COLUMN_NAME_BUILDING_TITLE + TEXT_TYPE +
                    ")";

    private static final String FLOOR_CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS " + Floors.TABLE_NAME + " (" +
                    Floors._ID + INTEGER_TYPE + " PRIMARY KEY, " +
                    Floors.COLUMN_CONFIG_PATH + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_MAP_PATH + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_MAP_GRAPH_PATH + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_MASK_PATH + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_BUILDING_ID + INTEGER_TYPE + COMA_SEP +
                    Floors.COLUMN_BUILDING_TITLE + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_NUMBER + INTEGER_TYPE + COMA_SEP +
                    Floors.COLUMN_SUBTITLE + TEXT_TYPE + COMA_SEP +
                    Floors.COLUMN_PIXEL_SIZE + REAL_TYPE + COMA_SEP +
                    Floors.COLUMN_WIDTH + REAL_TYPE + COMA_SEP +
                    Floors.COLUMN_HEIGHT + REAL_TYPE +
                    ")";

    private static final String BEACONS_CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS " + Beacons.TABLE_NAME + " (" +
                    Beacons.COLUMN_NAME_MAC_ADDRESS + TEXT_TYPE + " PRIMARY KEY, " +
                    Beacons.COLUMN_NAME_X + REAL_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_Y + REAL_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_Z + REAL_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_MAJOR + INTEGER_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_MINOR + INTEGER_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_DAMP + REAL_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_FLOOR_ID + INTEGER_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_FLOOR_NUMBER + INTEGER_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_BUILDING_ID + INTEGER_TYPE + COMA_SEP +
                    Beacons.COLUMN_NAME_BUILDING_TITLE + TEXT_TYPE +
                    ")";


    private static final String INDOR_MAPS_DELETE =
            "DROP TABLE IF EXISTS " + Buildings.TABLE_NAME;
    private static final String INPOINTS_DELETE =
            "DROP TABLE IF EXISTS " + Inpoints.TABLE_NAME;
    private static final String FLOOR_DELETE =
            "DROP TABLE IF EXISTS " + Floors.TABLE_NAME;
    private static final String BEACON_DELETE =
            "DROP TABLE IF EXISTS " + Beacons.TABLE_NAME;

    DbHelper(Context context) {
        super(context, DB_NAME, null, DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL(BUILDINGS_CREATE_TABLE);
        sqLiteDatabase.execSQL(INPOINTS_CREATE_TABLE);
        sqLiteDatabase.execSQL(FLOOR_CREATE_TABLE);
        sqLiteDatabase.execSQL(BEACONS_CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        sqLiteDatabase.execSQL(INDOR_MAPS_DELETE);
        sqLiteDatabase.execSQL(INPOINTS_DELETE);
        sqLiteDatabase.execSQL(FLOOR_DELETE);
        sqLiteDatabase.execSQL(BEACON_DELETE);

        onCreate(sqLiteDatabase);
    }
    static final class Buildings implements BaseColumns {
        static final String TABLE_NAME = "building";
        static final String COLUMN_NAME_TITLE = "title";
        static final String COLUMN_NAME_SUBTITLE = "subtitle";
        static final String COLUMN_NAME_OUTPOINT_ID = "outpoint_id";
        static final String COLUMN_NAME_CREATED_AT = "created_at";
        static final String COLUMN_NAME_UPDATED_AT = "updated_at";
        static final String COLUMN_NAME_POI_NAME = "poi_name";
    }

    static final class Floors implements BaseColumns {
        static final String TABLE_NAME = "floor";
        static final String COLUMN_CONFIG_PATH = "configPath";
        static final String COLUMN_MAP_PATH = "mapPath";
        static final String COLUMN_MAP_GRAPH_PATH = "graphPath";
        static final String COLUMN_MASK_PATH = "maskPath";
        static final String COLUMN_BUILDING_ID = "buildingId";
        static final String COLUMN_BUILDING_TITLE = "indoorMapTitle";
        static final String COLUMN_NUMBER = "number";
        static final String COLUMN_SUBTITLE = "subtitle";
        static final String COLUMN_PIXEL_SIZE = "pixelSize";
        static final String COLUMN_WIDTH = "width";
        static final String COLUMN_HEIGHT = "height";

    }

    static final class Inpoints implements BaseColumns {
        static final String TABLE_NAME = "inpoints";
        static final String COLUMN_NAME_FLOOR_ID = "floor_id";
        static final String COLUMN_NAME_TITLE = "title";
        static final String COLUMN_NAME_SUBTITLE = "subtitle";
        static final String COLUMN_NAME_DESCRIPTION = "description";
        static final String COLUMN_NAME_IMAGE = "image";
        static final String COLUMN_NAME_HINT = "hint";
        static final String COLUMN_NAME_TAGS = "tags";
        static final String COLUMN_NAME_TYPE = "type";
        static final String COLUMN_NAME_ICON_ID = "icon_id";
        static final String COLUMN_NAME_X = "x";
        static final String COLUMN_NAME_Y = "y";
        static final String COLUMN_NAME_NEAR_ROUTE_X = "near_route_x";
        static final String COLUMN_NAME_NEAR_ROUTE_Y = "near_route_y";
        static final String COLUMN_NAME_GPS_LAT = "gps_lat";
        static final String COLUMN_NAME_GPS_LON = "gps_lon";
        static final String COLUMN_NAME_GPS_ALT = "gps_alt";
        static final String COLUMN_NAME_CREATED_AT = "created_at";
        static final String COLUMN_NAME_UPDATED_AT = "updated_at";
        static final String COLUMN_NAME_FLOOR_NUMBER = "floor_number";
        static final String COLUMN_NAME_BUILDING_ID = "building_id";
        static final String COLUMN_NAME_BUILDING_TITLE = "building_title";
    }

    static final class Beacons {
        static final String TABLE_NAME = "beacons";
        static final String COLUMN_NAME_X = "x";
        static final String COLUMN_NAME_Y = "y";
        static final String COLUMN_NAME_Z = "z";
        static final String COLUMN_NAME_MAC_ADDRESS = "mac_address";
        static final String COLUMN_NAME_MAJOR = "major";
        static final String COLUMN_NAME_MINOR = "minor";
        static final String COLUMN_NAME_DAMP = "damp";
        static final String COLUMN_NAME_FLOOR_ID = "floor_id";
        static final String COLUMN_NAME_FLOOR_NUMBER = "floor_number";
        static final String COLUMN_NAME_BUILDING_ID = "building_id";
        static final String COLUMN_NAME_BUILDING_TITLE = "building_tiltle";

    }




}
