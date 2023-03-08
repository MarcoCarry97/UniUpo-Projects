package location.springlab.locationservices;

import android.content.Context;
import android.location.Location;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;

class LocAdapter extends ArrayAdapter<Location>
{
    private Context context;
    private int resource;
    private ArrayList<Location> data;

    public LocAdapter(Context applicationContext, int list_row, ArrayList<Location> locations)
    {
        super(applicationContext,list_row,locations);
        context=applicationContext;
        resource=list_row;
        data=locations;
    }

    @Override
    public int getCount()
    {
        return data.size();
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent)
    {
        convertView=View.inflate(context,resource,null);
        TextView lat,lng,name;
        lat=convertView.findViewById(R.id.lat);
        lng=convertView.findViewById(R.id.lng);
        name=convertView.findViewById(R.id.name);
        lat.setText(String.valueOf(data.get(position).getLatitude()));
        lng.setText(String.valueOf(data.get(position).getLongitude()));
        name.setText(data.get(position).getProvider());
        return convertView;
    }
}
