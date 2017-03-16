package khpi.com.demo.db;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import khpi.com.demo.model.Building;

import java.util.List;

public class BuildingRepository extends BaseRepository {

    BuildingRepository(SQLiteOpenHelper sqLiteOpenHelper) {
        super(sqLiteOpenHelper);
    }

    void saveBuildings(List<Building> buildings) {
        if (!canWriteToDatabase()) {
            openDatabase();
        }
        try {
            getDatabase().beginTransaction();
            for (Building building : buildings) {
                getDatabase().insertWithOnConflict(
                        DbHelper.Buildings.TABLE_NAME,
                        null,
                        Mapper.getBuildingContentValues(building),
                        SQLiteDatabase.CONFLICT_REPLACE
                );
            }
            getDatabase().setTransactionSuccessful();
        }
        finally {
            getDatabase().endTransaction();
        }
    }

    void saveBuilding(Building building) {
        if (!canWriteToDatabase()) {
            openDatabase();
        }

        try {
            getDatabase().beginTransaction();

            getDatabase().insertWithOnConflict(
                    DbHelper.Buildings.TABLE_NAME,
                    null,
                    Mapper.getBuildingContentValues(building),
                    SQLiteDatabase.CONFLICT_REPLACE
            );

            getDatabase().setTransactionSuccessful();
        } finally {
            getDatabase().endTransaction();
        }
    }

    List<Building> getBuildings() {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Buildings.TABLE_NAME,
                null,
                null,
                null,
                null,
                null,
                null
        );

        return Mapper.buildings(query);
    }

    List<Building> getBuildingsByOutpointId(long id) {
        if (!isDatabaseOpen()) {
            openDatabase();
        }

        Cursor query = getDatabase().query(
                DbHelper.Buildings.TABLE_NAME,
                null,
                DbHelper.Buildings.COLUMN_NAME_OUTPOINT_ID + "=?",
                new String[]{String.valueOf(id)},
                null,
                null,
                null
        );

        return Mapper.buildings(query);
    }

}
