package location.springlab.locationservices;

import android.content.Context;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Toast;

public class DatabaseHelper extends SQLiteOpenHelper {

    // Table Name
    public static final String TABLE_NAME = "LOCATIONS";

    // Table columns
    public static final String ID = "id";
    public static final String LAT = "transition type";
    public static final String LNG = "transition time";
    public static final String NAME ="transition name";

    // Database Information
    static final String DB_NAME = "LOCATIONS.DB";

    // database version
    static final int DB_VERSION = 1;

    // Creating table query
    private static final String CREATE_TABLE ="create table "
            + TABLE_NAME
            + "(" + ID
            + " INTEGER PRIMARY KEY AUTOINCREMENT, "
            + LAT + "DOUB, "
            + LNG + "DOUB, "
            + NAME + "TEXT);";

    public DatabaseHelper(Context context)
    {
        super(context, DB_NAME, null, DB_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db)
    {
        db.execSQL(CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
    {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }
}
