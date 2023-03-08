package map.springlab.mapultimate;

import android.app.IntentService;
import android.content.Intent;
import android.util.Log;

//import com.google.android.gms.location.Geofence;
//import com.google.android.gms.location.GeofencingEvent;

import java.util.List;

import static android.content.ContentValues.TAG;

public class GeofenceService extends IntentService
{

    /**
     * Creates an IntentService.  Invoked by your subclass's constructor.
     *
     * @param name Used to name the worker thread, important only for debugging.
     */
    public GeofenceService(String name)
    {
        super(name);
    }

    @Override
    protected void onHandleIntent( Intent intent)
    {
       /* GeofencingEvent geoEvent=GeofencingEvent.fromIntent(intent);
        if(geoEvent.hasError())
        {
            Log.e(TAG,"Geofence event has some error");
            return;
        }
        List<Geofence> geoTrigger=geoEvent.getTriggeringGeofences();
        int getoType=geoEvent.getGeofenceTransition();
        if(getoType==Geofence.GEOFENCE_TRANSITION_ENTER)
        {

        }
        else if(getoType==Geofence.GEOFENCE_TRANSITION_EXIT)
        {

        }
        else if(getoType==Geofence.GEOFENCE_TRANSITION_DWELL)
        {

        }*/
    }
}
