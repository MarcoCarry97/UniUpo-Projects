package location.springlab.locationservices;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.widget.Toast;

public class DBManager {

    private DatabaseHelper dbHelper;

    private Context context;

    private SQLiteDatabase database;

    public DBManager(Context c) {
        context = c;
    }

    public void open() throws SQLException
    {
        dbHelper = new DatabaseHelper(context);
        try
        {
            database=dbHelper.getWritableDatabase();
        }
        catch (SQLException e)
        {
            Toast.makeText(context,"eccezione",Toast.LENGTH_SHORT).show();
        }
    }

    public void close() {
        dbHelper.close();
    }

    public void insert(double lat, double lng,String name) {
        ContentValues contentValue = new ContentValues();
        contentValue.put(DatabaseHelper.LAT, lat);
        contentValue.put(DatabaseHelper.LNG, lng);
        contentValue.put(DatabaseHelper.NAME,name);
        database.insert(DatabaseHelper.TABLE_NAME, null, contentValue);
    }

    public Cursor fetch() {
        String[] columns = new String[] { DatabaseHelper.ID, DatabaseHelper.LAT, DatabaseHelper.LNG,DatabaseHelper.NAME };
        Cursor cursor = database.query(DatabaseHelper.TABLE_NAME, columns, null, null, null, null, null);
        if (cursor != null) {
            cursor.moveToFirst();
        }
        return cursor;
    }

    public int update(long _id,double lat, double lng,String name) {
        ContentValues contentValues = new ContentValues();
        contentValues.put(DatabaseHelper.LAT, lat);
        contentValues.put(DatabaseHelper.LNG, lng);
        contentValues.put(DatabaseHelper.NAME,name);
        int i = database.update(DatabaseHelper.TABLE_NAME, contentValues, DatabaseHelper.ID + " = " + _id, null);
        return i;
    }

    public void delete(long _id) {
        database.delete(DatabaseHelper.TABLE_NAME, DatabaseHelper.ID + "=" + _id, null);
    }

}
