package khpi.com.demo.db;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import khpi.com.demo.model.Floor;

import java.util.List;


public class FloorRepository extends BaseRepository {

    FloorRepository(SQLiteOpenHelper openHelper){
        super(openHelper);
    }

    void saveFloors(List<Floor> floors){
        if(!canWriteToDatabase()){
            openDatabase();
        }

        try {
            getDatabase().beginTransaction();
            for (Floor floor : floors) {
                getDatabase().insertWithOnConflict(
                        DbHelper.Floors.TABLE_NAME,
                        null,
                        Mapper.getFloorContentValue(floor),
                        SQLiteDatabase.CONFLICT_REPLACE
                );
            }
            getDatabase().setTransactionSuccessful();
        }
        finally {
            getDatabase().endTransaction();
        }
    }

    void saveFloor(Floor floor){
        if(!canWriteToDatabase()){
            openDatabase();
        }

        try{
            getDatabase().beginTransaction();
            getDatabase().insertWithOnConflict(
                    DbHelper.Floors.TABLE_NAME,
                    null,
                    Mapper.getFloorContentValue(floor),
                    SQLiteDatabase.CONFLICT_REPLACE
                    );
            getDatabase().setTransactionSuccessful();
        }
        finally {
            getDatabase().endTransaction();
        }
    }

    List<Floor> getFloors() {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Floors.TABLE_NAME,
                null,
                null,
                null,
                null,
                null,
                null
        );

        return Mapper.floors(query);
    }

    Floor getFloorById(long id){
        Cursor query = getDatabase().query(
                DbHelper.Floors.TABLE_NAME,
                null,
                DbHelper.Floors._ID + "=?",
                new String[]{String.valueOf(id)},
                null,
                null,
                null
        );
        return Mapper.cursorToFloor(query);
    }

    List<Floor> getFloorsByBuildingId(long id){
        Cursor query = getDatabase().query(
                DbHelper.Floors.TABLE_NAME,
                null,
                DbHelper.Floors.COLUMN_BUILDING_ID + "=?",
                new String[]{String.valueOf(id)},
                null,
                null,
                null
        );
        return Mapper.floors(query);
    }
}
