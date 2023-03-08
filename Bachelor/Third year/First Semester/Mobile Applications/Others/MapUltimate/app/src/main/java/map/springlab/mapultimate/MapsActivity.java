package map.springlab.mapultimate;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MapsActivity extends AppCompatActivity implements OnMapReadyCallback
{
    private int mapType = 0;
    private static final String TAG = "";
    private GoogleMap map;
    private MarkerOptions uniupo;
    private ArrayList<MarkerOptions> other;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager().findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }

    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu, menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        switch (item.getItemId())
        {
            case (R.id.change):
                mapType = map.getMapType() + 1 % 5;
                map.setMapType(mapType);
                break;
            case (R.id.increase):
                setZoom(map, 30);
                break;
            case (R.id.decrease):
                setZoom(map, 10);
                break;
            case (R.id.center):
                centerOnAMarker(map, uniupo);
        }
        return super.onOptionsItemSelected(item);
    }

    private void centerOnAMarker(GoogleMap map, MarkerOptions marker)
    {
        float tilt = map.getCameraPosition().tilt;
        float zoom = map.getCameraPosition().zoom;
        updateCameraPosition(map, tilt, zoom, marker.getPosition());
    }

    private void setZoom(GoogleMap map, float zoom)
    {
        updateCameraPosition(map, 45, zoom, map.getCameraPosition().target);
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
    public void onMapReady(final GoogleMap googleMap)
    {
        map = googleMap;
        //apiConnection();
        if (uniupo != null) map.addMarker(uniupo);
        else {
            LatLng latLng = new LatLng(44.9237555, 8.6179071);
            uniupo = addMarkerOnMap(googleMap, latLng, "UNIUPO", BitmapDescriptorFactory.HUE_AZURE);
        }
        if (other != null)
            for (MarkerOptions marker : other)
                map.addMarker(marker);
        else {
            other = new ArrayList<MarkerOptions>();
            HashMap<String, LatLng> bikes = createBKhash();
            for (Map.Entry<String, LatLng> entry : bikes.entrySet())
                other.add(addMarkerOnMap(googleMap, entry.getValue(), entry.getKey(), BitmapDescriptorFactory.HUE_RED));
        }
        if(mapType!=map.getMapType()) mapType=map.getMapType();
        else mapType=map.getMapType();
        googleMap.setOnMarkerClickListener(new GoogleMap.OnMarkerClickListener() {
            @Override
            public boolean onMarkerClick(Marker marker) {
                float distance = (float) haversine(uniupo.getPosition(), marker.getPosition());
                String unit = "Km";
                if (distance < 1) {
                    distance *= 10;
                    unit = "Hm";
                }
                if (distance < 1) {
                    distance *= 10;
                    unit = "Dm";
                }
                if (distance != 0)
                    while (distance < 1) {
                        distance *= 10;
                        unit = "m";
                    }
                else unit = "m";
                toastMessage(String.valueOf(distance) + " " + unit);
                return false;
            }
        });
        googleMap.setOnMapClickListener(new GoogleMap.OnMapClickListener() {
            @Override
            public void onMapClick(LatLng latLng) {
                LoadMarkerAsync loadMarkerAsync = new LoadMarkerAsync(getApplicationContext(), googleMap, other);
                loadMarkerAsync.execute(latLng);
            }
        });
    }

    private MarkerOptions addMarkerOnMap(GoogleMap map, LatLng latLng, String title, float colour)
    {
        MarkerOptions marker = new MarkerOptions();
        marker.position(latLng);
        marker.title(title);
        marker.icon(BitmapDescriptorFactory.defaultMarker(colour));
        map.addMarker(marker);
        updateCameraPosition(map, 45, 16, latLng);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return null;
        }
        map.setMyLocationEnabled(true);
        return marker;
    }

    private void updateCameraPosition(GoogleMap map, float tilt, float zoom, LatLng latLng)
    {
        CameraPosition camera;
        camera=new CameraPosition.Builder().target(latLng).tilt(tilt).zoom(zoom).build();
        map.animateCamera(CameraUpdateFactory.newCameraPosition(camera),3000,null);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED)
            return;
        map.setMyLocationEnabled(true);

    }

    protected void onResume()
    {
        super.onResume();
        Log.i("AFL","OnResume");
        if (ActivityCompat.checkSelfPermission(this,
                Manifest.permission.ACCESS_FINE_LOCATION) !=
                PackageManager.PERMISSION_GRANTED)
        {
            Log.e(TAG,"Fine location permission not granted");
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION},777);
        }
        else Log.i("AFL","Fine location permission granted!");
    }

    private HashMap<String, LatLng> createBKhash() {
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

    private  void toastMessage(String message)
    {
        Toast.makeText(getApplicationContext(),message,Toast.LENGTH_SHORT).show();
    }

    static double haversine(LatLng p, LatLng t) {
        double lon1 = Math.toRadians(p.longitude);
        double lat1 = Math.toRadians(p.latitude);
        double lon2 = Math.toRadians(t.longitude);
        double lat2 = Math.toRadians(t.latitude);
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = Math.pow(Math.sin(dlat / 2), 2) +
                Math.cos(lat1) * Math.cos(lat2) * Math.pow(Math.sin(dlon / 2), 2);
        double c = 2 * Math.asin(Math.sqrt(a));
        return (6367 * c);     // 6367 is Earth radius in Km
    }

     @Override
    protected void onSaveInstanceState(Bundle outState)
    {
        super.onSaveInstanceState(outState);
        outState.putParcelable("uniupo", uniupo);
        outState.putParcelableArrayList("other",other);
        outState.putInt("mapType",map.getMapType());
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState)
    {
        super.onRestoreInstanceState(savedInstanceState);
        uniupo=savedInstanceState.getParcelable("uniupo");
        other=savedInstanceState.getParcelableArrayList("other");
        mapType=savedInstanceState.getInt("mapType");
    }
}
