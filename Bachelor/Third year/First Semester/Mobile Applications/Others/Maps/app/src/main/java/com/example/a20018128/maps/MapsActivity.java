package com.example.a20018128.maps;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.util.HashMap;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {

    private GoogleMap mMap;

    private HashMap<String, LatLng> createBKhash()
    {
        HashMap<String, LatLng> h = new HashMap<String, LatLng>();
        h.put("Garibaldi", new LatLng(44.909045, 8.614381));
        h.put("Marengo", new LatLng(44.916316, 8.623474));
        h.put("Municipio", new LatLng(44.913129, 8.615593));
        h.put("Park Multipiano", new LatLng(44.911780, 8.620137));
        h.put("Piazza Libertà", new LatLng(44.913585, 8.615443));
        h.put("Università", new LatLng(44.922667, 8.616993));
        h.put("Stazione FF.SS.", new LatLng(44.909083, 8.607788));
        h.put("Cittadella", new LatLng(44.924156, 8.611135));
        h.put("Carducci", new LatLng(44.913527, 8.610126));
        h.put("Provvidenza", new LatLng(44.920897, 8.620121));
        return h;
    }


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap)
    {

        // Add a marker in Sydney and move the camera
        addMarkerOnMap(googleMap, -34, 151, "Sydney");
        addMarkerOnMap(googleMap,44.9237555,8.6179071,"DISIT");
        HashMap<String,LatLng> bikes=createBKhash();
        for(HashMap.Entry<String,LatLng> entry:bikes.entrySet())
        {
            String s=entry.getKey();
            LatLng latLng=entry.getValue();
            addMarkerOnMap(googleMap,latLng,s);
        }
    }

    private void addMarkerOnMap(GoogleMap map, double lat, double lng, String message) {
        mMap = map;
        LatLng latLng = new LatLng(lat, lng);
        MarkerOptions marker = new MarkerOptions();
        marker.position(latLng);
        marker.title(message);
        marker.icon(BitmapDescriptorFactory.defaultMarker(getMarkerColour(latLng)));
        mMap.addMarker(new MarkerOptions().position(latLng).title(message));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(latLng));
        CameraPosition camera = new CameraPosition.Builder().target(latLng).tilt(45).zoom(16).build();
        mMap.animateCamera(CameraUpdateFactory.newCameraPosition(camera), 3000, null);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        mMap.setMyLocationEnabled(true);
    }

    private void addMarkerOnMap(GoogleMap map, LatLng latLng, String message)
    {
        addMarkerOnMap(map,latLng.latitude,latLng.longitude,message);
    }

    private float getMarkerColour(LatLng latLng)
    {
        LatLng tmp=new LatLng(44.9237555,8.6179071);
        if(tmp.latitude==latLng.latitude && tmp.longitude==latLng.longitude)
        {
            toastMessage("Blu");
            return BitmapDescriptorFactory.HUE_BLUE;
        }
        else return BitmapDescriptorFactory.HUE_RED;
    }

    private void toastMessage(String message)
    {
        Toast.makeText(getApplicationContext(),message,Toast.LENGTH_SHORT).show();
    }
}
