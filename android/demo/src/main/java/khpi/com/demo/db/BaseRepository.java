package khpi.com.demo.db;

import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

abstract class BaseRepository {

    private SQLiteDatabase database;
    private final SQLiteOpenHelper sqLiteOpenHelper;

    BaseRepository(SQLiteOpenHelper sqLiteOpenHelper) {
        this.sqLiteOpenHelper = sqLiteOpenHelper;
        database = sqLiteOpenHelper.getWritableDatabase();
    }

    protected SQLiteDatabase getDatabase() {
        return database;
    }

    protected boolean canWriteToDatabase() {
        return !database.isOpen() || !database.isReadOnly();
    }

    protected boolean isDatabaseOpen() {
        return database.isOpen();
    }

    protected void openDatabase() {
        database = sqLiteOpenHelper.getWritableDatabase();
    }



}
