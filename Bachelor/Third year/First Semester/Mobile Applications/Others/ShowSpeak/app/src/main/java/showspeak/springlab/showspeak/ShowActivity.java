package showspeak.springlab.showspeak;

import android.content.Intent;
import android.graphics.Bitmap;
import android.media.Image;
import android.os.Build;
import android.speech.tts.TextToSpeech;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

import java.util.Locale;

public class ShowActivity extends AppCompatActivity implements TextToSpeech.OnInitListener
{
    final int CAPTURE_CODE=1;
    private ImageView image;
    private Button back;
    private Button repeat;
    private TextToSpeech speech;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show);
        speech=new TextToSpeech(this,this);
        image=findViewById(R.id.image);
        back=findViewById(R.id.back);
        repeat=findViewById(R.id.repeat);
        back.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent intent=new Intent(getApplicationContext(),MainActivity.class);
                startActivity(intent);
            }
        });
        repeat.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                textToSpeak(getIntent().getExtras().getString("text"));
            }
        });
        Bundle bundle=getIntent().getExtras();
        Bitmap bitmap= (Bitmap) bundle.get("data");
        image.setImageBitmap(bitmap);
    }

    @Override
    public void onInit(int status) {
        Bundle bundle=getIntent().getExtras();
        String language=bundle.getString("language");
        String text=bundle.getString("text");
        if (status == TextToSpeech.SUCCESS) {
            int result = speech.setLanguage(getLanguage(language));
            if (result == TextToSpeech.LANG_MISSING_DATA || result == TextToSpeech.LANG_NOT_SUPPORTED) {
                Log.e("error", "This Language is not supported");
            } else {
                textToSpeak(text);
            }
        } else {
            Log.e("error", "Failed to Initialize");
        }
    }

    private Locale getLanguage(String language)
    {
        Locale ret=null;
        switch (language)
        {
            case("EN"): ret=Locale.ENGLISH; break;
            case("FR"): ret=Locale.FRENCH; break;
            case("IT"): ret=Locale.ITALIAN; break;
            case("DE"): ret=Locale.GERMAN; break;
            case("ES"): ret=Locale.CHINESE; break;
            default: ret=Locale.US; break;
        }
        return ret;
    }

    private void textToSpeak(String text)
    {
        if ("".equals(text))
            text = "Please enter some text to speak.";
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP)
            speech.speak(text, TextToSpeech.QUEUE_FLUSH, null, null);
        else speech.speak(text, TextToSpeech.QUEUE_FLUSH, null);
    }
}
