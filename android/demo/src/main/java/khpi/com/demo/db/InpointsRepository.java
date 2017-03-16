package khpi.com.demo.db;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import khpi.com.demo.model.Inpoint;

import java.util.List;

public class InpointsRepository extends BaseRepository {

    InpointsRepository(SQLiteOpenHelper sqLiteOpenHelper) {
        super(sqLiteOpenHelper);
    }

    void saveAll(List<Inpoint> inpoints) {
        if (!canWriteToDatabase()) {
            openDatabase();
        }
        try {
            getDatabase().beginTransaction();

            for (Inpoint point : inpoints) {
                getDatabase().insertWithOnConflict(
                        DbHelper.Inpoints.TABLE_NAME,
                        null,
                        Mapper.getInpointContentValues(point),
                        SQLiteDatabase.CONFLICT_REPLACE
                );
            }
            getDatabase().setTransactionSuccessful();
        }
        finally {
            getDatabase().endTransaction();
        }

    }

    void save(Inpoint inpoint) {
        if (!canWriteToDatabase()) {
            openDatabase();
        }

        try {
            getDatabase().beginTransaction();

            getDatabase().insertWithOnConflict(
                    DbHelper.Inpoints.TABLE_NAME,
                    null,
                    Mapper.getInpointContentValues(inpoint),
                    SQLiteDatabase.CONFLICT_REPLACE
            );

            getDatabase().setTransactionSuccessful();
        } finally {
            getDatabase().endTransaction();
        }
    }

    List<Inpoint> getInpoints() {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Inpoints.TABLE_NAME,
                null,
                null,
                null,
                null,
                null,
                null
        );


        return Mapper.inpoints(query);
    }

    List<Inpoint> getInpointsByBuildingAndFloorId(long id, int floorId) {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Inpoints.TABLE_NAME,
                null,
                DbHelper.Inpoints.COLUMN_NAME_BUILDING_ID + "=? AND " + DbHelper.Inpoints.COLUMN_NAME_FLOOR_ID +"=?",
                new String[]{String.valueOf(id), String.valueOf(floorId)},
                null,
                null,
                null
        );


        return Mapper.inpoints(query);
    }

    List<Inpoint> getInpointsByFloorId(int floorId) {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Inpoints.TABLE_NAME,
                null,
                DbHelper.Inpoints.COLUMN_NAME_FLOOR_ID +"=?",
                new String[]{String.valueOf(floorId)},
                null,
                null,
                null
        );


        return Mapper.inpoints(query);
    }

    List<Integer> getInpointsIdByFloorId(int floorId) {
        if (!isDatabaseOpen()) {
            openDatabase();
        }
        Cursor query = getDatabase().query(
                DbHelper.Inpoints.TABLE_NAME,
                new String[]{DbHelper.Inpoints._ID},
                DbHelper.Inpoints.COLUMN_NAME_FLOOR_ID +"=?",
                new String[]{String.valueOf(floorId)},
                null,
                null,
                null
        );


        return Mapper.inpointsId(query);
    }


    Inpoint getInpointById(int id) {
        if (!isDatabaseOpen()) {
            openDatabase();
        }
        Cursor query = getDatabase().query(
                DbHelper.Inpoints.TABLE_NAME,
                null,
                DbHelper.Inpoints._ID +"=?",
                new String[]{String.valueOf(String.valueOf(id))},
                null,
                null,
                null
        );

        return Mapper.inpoint(query);
    }



}
