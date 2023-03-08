package map.springlab.mapultimate;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.location.Address;
import android.location.Geocoder;
import android.os.AsyncTask;
import android.support.annotation.UiThread;
import android.support.v4.app.ActivityCompat;
import android.widget.Toast;

//import com.google.android.gms.location.Geofence;
//import com.google.android.gms.location.GeofencingRequest;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.CameraPosition;
import com.google.android.gms.maps.model.CircleOptions;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class LoadMarkerAsync extends AsyncTask<LatLng, Address, LatLng> {
    private Context context;
    private GoogleMap map;
    private Geocoder geocoder;
    private ArrayList<MarkerOptions> markers;
    private ArrayList<CircleOptions> circles;

    public LoadMarkerAsync(Context context, GoogleMap map, ArrayList<MarkerOptions> markers/*, ArrayList<Geofence> geofences, ArrayList<CircleOptions> circles*/) {
        this.context = context;
        this.map = map;
        geocoder = new Geocoder(context);
        this.markers = markers;
    }

    @Override
    protected LatLng doInBackground(LatLng... latLngs) {
        LatLng latLng = latLngs[0];
        try {
            List<Address> addresses = geocoder.getFromLocation(latLng.latitude, latLng.longitude, 1);
            publishProgress(addresses.get(0));
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(Address... values) {
        super.onProgressUpdate(values);
        Address address = values[0];
        LatLng latLng = new LatLng(address.getLatitude(), address.getLongitude());
        markers.add(addMarkerOnMap(map, latLng, address.getAddressLine(0), BitmapDescriptorFactory.HUE_YELLOW));
    }

    private MarkerOptions addMarkerOnMap(GoogleMap map, LatLng latLng, String title, float colour) {
        MarkerOptions marker = new MarkerOptions();
        marker.position(latLng);
        marker.title(title);
        marker.icon(BitmapDescriptorFactory.defaultMarker(colour));
        map.addMarker(marker);
        CameraPosition camera = new CameraPosition.Builder().target(latLng).tilt(45).zoom(16).build();
        map.animateCamera(CameraUpdateFactory.newCameraPosition(camera), 1000, null);
        if (ActivityCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return null;
        }
        map.setMyLocationEnabled(true);
        return marker;
    }

    private  void toastMessage(String message)
    {
        Toast.makeText(context,message,Toast.LENGTH_SHORT).show();
    }
}
