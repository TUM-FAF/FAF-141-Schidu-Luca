package com.example.schidu.pomodoro;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

import com.example.schidu.pomodoro.database.SessionEntity;
import com.mikhaellopez.circularprogressbar.CircularProgressBar;
import com.orm.SugarContext;

public class MainActivity extends AppCompatActivity {

    CircularProgressBar circularProgressBar;
    TextView timeTextView;
    FloatingActionButton fab;
    MainPresenter mainPresenter;
    boolean started = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        initWidgets();
        SugarContext.init(getApplicationContext());

        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(!started) {
                    fab.setImageDrawable(getResources().getDrawable(android.R.drawable.ic_media_pause));
                    started = true;
                    mainPresenter.startTimer();
                }else {
                    started = false;
                    fab.setImageDrawable(getResources().getDrawable(android.R.drawable.ic_media_play));
                    mainPresenter.stopTimer();
                    timeTextView.setText(R.string.time);
                    circularProgressBar.setProgress(100);
                }
            }
        });
    }


    public void initWidgets() {
        circularProgressBar = (CircularProgressBar)findViewById(R.id.view);
        timeTextView = (TextView) findViewById(R.id.timeTextView);
        fab = (FloatingActionButton) findViewById(R.id.fab);
        mainPresenter = new MainPresenter();
        mainPresenter.onTakeView(this);
        circularProgressBar.setProgress(100);
    }

    public void getData(String time, int progress) {
        timeTextView.setText(time);
        circularProgressBar.setProgress(progress);
    }



    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        int id = item.getItemId();

        if (id == R.id.action_settings) {
            startActivity(new Intent(this, Statistics.class));
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
