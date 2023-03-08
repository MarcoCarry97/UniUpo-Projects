package showspeak.springlab.showspeak;

import android.content.Intent;
import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity
{
    private ListView listView;
    private Intent intent;
    final int CAPTURE_CODE=1;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        intent=new Intent(getApplicationContext(),ShowActivity.class);
        String data[]={"IT","EN","CH","FR","DE"};
        List<ListItem> list=new ArrayList<ListItem>();
        for(String s:data)
            list.add(new ListItem(s));
        listView=findViewById(R.id.list);
        ItemAdapter adapter=new ItemAdapter(getApplicationContext(),this,intent,R.layout.list_item,list);
        listView.setAdapter(adapter);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == CAPTURE_CODE)
        {
            if (resultCode == RESULT_OK)
                intent.putExtras(data.getExtras());
            else if (resultCode == RESULT_CANCELED)
                Toast.makeText(getApplicationContext(), "Cancelled", Toast.LENGTH_LONG).show();
        }
    }

}
