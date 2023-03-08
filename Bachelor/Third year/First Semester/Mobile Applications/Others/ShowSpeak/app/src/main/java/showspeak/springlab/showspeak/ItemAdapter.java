package showspeak.springlab.showspeak;

import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.List;

public class ItemAdapter extends ArrayAdapter<ListItem>
{
    final int CAPTURE_CODE=1;

    private Context context;
    private MainActivity main;
    private Intent intent;
    private List<ListItem> languages;

    public ItemAdapter(Context context,MainActivity main,Intent intent, int resource,List<ListItem> languages)
    {
        super(context, resource);
        this.context=context;
        this.languages=languages;
        this.main=main;
        this.intent=intent;
    }

    @Override
    public int getCount()
    {
        return languages.size();
    }

    @NonNull
    @Override
    public View getView(final int position, @Nullable View convertView, @NonNull ViewGroup parent)
    {
        convertView=View.inflate(context,R.layout.list_item,null);
        Button showButton=convertView.findViewById(R.id.show);
        String name=showButton.getText().toString();
        name+="-"+languages.get(position).getLanguage();
        showButton.setText(name);
        Button takePic=convertView.findViewById(R.id.take);
        final EditText typeText=convertView.findViewById(R.id.type);
        showButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                intent.putExtra("text",typeText.getText().toString());
                intent.putExtra("language",languages.get(position).getLanguage());
                context.startActivity(intent);
            }
        });
        takePic.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent=new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                main.startActivityForResult(intent,CAPTURE_CODE);
            }
        });
        return convertView;
    }


}
