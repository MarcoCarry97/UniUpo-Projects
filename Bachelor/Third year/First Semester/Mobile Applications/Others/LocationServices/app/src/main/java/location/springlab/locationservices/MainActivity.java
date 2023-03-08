package location.springlab.locationservices;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.database.SQLException;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GoogleApiAvailability;
import com.google.android.gms.location.FusedLocationProviderClient;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static android.Manifest.permission.ACCESS_FINE_LOCATION;
import static android.content.pm.PackageManager.PERMISSION_GRANTED;


public class MainActivity extends AppCompatActivity
{
    private Button get;
    private ListView listLocal;
    private final int LOCATION_PERMISSION_REQUEST=1;
    //private DBManager dbManager;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //dbManager=new DBManager(getApplicationContext());
        listLocal = findViewById(R.id.location);
        get = findViewById(R.id.button);
        get.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                GoogleApiAvailability availability = GoogleApiAvailability.getInstance();
                int result = availability.isGooglePlayServicesAvailable(getApplicationContext());
                if (result != ConnectionResult.SUCCESS) {
                    if (!availability.isUserResolvableError(result))
                        Toast.makeText(getApplicationContext(), "The service is not available", Toast.LENGTH_SHORT).show();
                }
                else controlPermission();
            }
        });
    }

   /* @Override
    public void onRequestPermissionsResult(int requestCode,  String[] permissions, int[] grantResults)
    {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == LOCATION_PERMISSION_REQUEST)
        {
            if (grantResults[0] != PERMISSION_GRANTED)
                Toast.makeText(this, "Location Permission Denied", Toast.LENGTH_LONG).show();
            else writeLocation();
        }
    }*/

    private void controlPermission()
    {
        int permission = ActivityCompat.checkSelfPermission(this,Manifest.permission.ACCESS_FINE_LOCATION);
        if (permission == PERMISSION_GRANTED) writeLocation();
        else ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_PERMISSION_REQUEST);
    }

    private void writeLocation()
    {
        FusedLocationProviderClient fused = LocationServices.getFusedLocationProviderClient(getApplicationContext());
        if (ActivityCompat.checkSelfPermission(this, ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, android.Manifest.permission.ACCESS_COARSE_LOCATION) == PackageManager.PERMISSION_GRANTED)
        {
            toastMessage("dentro");
            fused.getLastLocation().addOnSuccessListener(this, new OnSuccessListener<Location>()
            {
                @Override
                public void onSuccess(Location location)
                {
                    if (location != null) writeOnDatabase(location);
                   // else showOtherLocations();
                }
            });
            fused.getLastLocation().addOnFailureListener(this, new OnFailureListener() {
                @Override
                public void onFailure(@NonNull Exception e)
                {
                    toastMessage("fail");
                }
            });
        }

    }

    private void writeOnDatabase(Location location)
    {
        DBManager dbManager = new DBManager(getApplicationContext());
        dbManager.open();
        //dbManager.insert(location.getLatitude(),location.getLongitude(),location.getProvider());
        //dbManager.close();
        //showOtherLocations();
    }

    private void showOtherLocations()
    {
        toastMessage("mostro tutte le altre");
        DBManager dbManager=new DBManager(getApplicationContext());
        dbManager.open();
        Cursor cursor=dbManager.fetch();
        ArrayList<Location> locations=getLocations(cursor);
        LocAdapter adapter=new LocAdapter(getApplicationContext(),R.layout.list_row,locations);
        listLocal.setAdapter(adapter);
        dbManager.close();
    }

    private ArrayList<Location> getLocations(Cursor cursor)
    {
        ArrayList<Location> loc=new ArrayList<Location>();
        while (cursor.moveToNext())
        {
            String name=cursor.getString(cursor.getColumnIndexOrThrow(DatabaseHelper.NAME));
            double lat=cursor.getDouble(cursor.getColumnIndexOrThrow(DatabaseHelper.LAT));
            double lng=cursor.getDouble(cursor.getColumnIndexOrThrow(DatabaseHelper.LNG));
            Location location=new Location(name);
            location.setLatitude(lat);
            location.setLongitude(lng);
            loc.add(location);
        }
        return loc;
    }

    private void  toastMessage(String message)
    {
        Toast.makeText(getApplicationContext(),message,Toast.LENGTH_SHORT).show();
    }
}