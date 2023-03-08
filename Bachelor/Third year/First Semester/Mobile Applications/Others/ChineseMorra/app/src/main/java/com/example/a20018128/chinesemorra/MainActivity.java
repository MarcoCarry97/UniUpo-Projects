package com.example.a20018128.chinesemorra;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;

public class MainActivity extends AppCompatActivity
{
    private RadioGroup difficult, choose;
    private final int EASY=-1, IMPOSSIBLE=-2, ROCK=1, SCISSORS=2, PAPER=3;
    private Button go;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        difficult=findViewById(R.id.group1);
        choose=findViewById(R.id.group2);
        go=findViewById(R.id.button1);
        go.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                int computerChoose=0, myChoose=0;
                int stateDiff=(difficult.getCheckedRadioButtonId()==R.id.radio1group1) ? EASY : IMPOSSIBLE;
                if(stateDiff==EASY)
                {
                    computerChoose = (int) (((Math.random()*100)%3)+1);
                    myChoose=getChooseFromRadio();
                }
                else if(stateDiff==IMPOSSIBLE)
                {
                    myChoose=getChooseFromRadio();
                    if(myChoose==SCISSORS) computerChoose=ROCK;
                    else if(myChoose==ROCK) computerChoose=PAPER;
                    else if(myChoose==PAPER) computerChoose=SCISSORS;
                }
                printWinner(myChoose,computerChoose);
            }
        });
    }
    private int getChooseFromRadio()
    {
        switch (choose.getCheckedRadioButtonId())
        {
            case R.id.radio1group2:
                return ROCK;
            case R.id.radio2group2:
                return SCISSORS;
            case R.id.radio3group2:
                return PAPER;
        }
        return 4;
    }

    private void printWinner(int myChoose, int computerChoose)
    {
        String result="";
        if(myChoose==computerChoose) result=getString(R.string.pair);
        else if(myChoose==SCISSORS && computerChoose==ROCK) result=getString(R.string.lose);
        else if(myChoose==ROCK && computerChoose==PAPER) result=getString(R.string.lose);
        else if(myChoose==PAPER && computerChoose==SCISSORS) result=getString(R.string.lose);
        else if(myChoose==SCISSORS && computerChoose==PAPER) result=getString(R.string.win);
        else if(myChoose==ROCK && computerChoose==SCISSORS) result=getString(R.string.win);
        else if(myChoose==PAPER && computerChoose==ROCK) result=getString(R.string.win);
        Toast.makeText(MainActivity.this,result,Toast.LENGTH_LONG).show();
    }
}
