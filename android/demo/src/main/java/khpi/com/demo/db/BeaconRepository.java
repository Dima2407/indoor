package khpi.com.demo.db;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import khpi.com.demo.model.BeaconModel;

import java.util.List;


public class BeaconRepository extends BaseRepository {

    BeaconRepository(SQLiteOpenHelper sqLiteOpenHelper) {
        super(sqLiteOpenHelper);
    }

    void saveBeacons(List<BeaconModel> beacons){
        if (!canWriteToDatabase()) {
            openDatabase();
        }

        try{
            for(BeaconModel beacon : beacons){
                getDatabase().insertWithOnConflict(
                        DbHelper.Buildings.TABLE_NAME,
                        null,
                        Mapper.getBeaconContentValues(beacon),
                        SQLiteDatabase.CONFLICT_REPLACE
                );
            }
            getDatabase().setTransactionSuccessful();
        }finally {
            getDatabase().endTransaction();
        }
    }

    void saveBeacon(BeaconModel beacon){
        if (!canWriteToDatabase()) {
            openDatabase();
        }

        try {
            getDatabase().beginTransaction();

            getDatabase().insertWithOnConflict(
                    DbHelper.Beacons.TABLE_NAME,
                    null,
                    Mapper.getBeaconContentValues(beacon),
                    SQLiteDatabase.CONFLICT_REPLACE
            );

            getDatabase().setTransactionSuccessful();
        } finally {
            getDatabase().endTransaction();
        }
    }

    BeaconModel getBeaconByMacAddress(String macAddress){
        Cursor query = getDatabase().query(
                DbHelper.Beacons.TABLE_NAME,
                null,
                DbHelper.Beacons.COLUMN_NAME_MAC_ADDRESS + "=?",
                new String[]{macAddress},
                null,
                null,
                null
        );
        return Mapper.cursorToBeaconModel(query);
    }

    List<BeaconModel> getBeaconsByFloorId(long id){
        Cursor query = getDatabase().query(
                DbHelper.Beacons.TABLE_NAME,
                null,
                DbHelper.Beacons.COLUMN_NAME_FLOOR_ID + "=?",
                new String[]{String.valueOf(id)},
                null,
                null,
                null
        );
        return Mapper.beacons(query);
    }


}
