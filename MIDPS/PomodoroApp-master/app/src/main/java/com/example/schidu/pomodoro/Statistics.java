package com.example.schidu.pomodoro;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ListView;

import com.example.schidu.pomodoro.adapters.CellAdapter;
import com.example.schidu.pomodoro.database.SessionEntity;
import java.util.List;

public class Statistics extends AppCompatActivity {

    ListView listView;
    List<SessionEntity> list;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_statistics);
        setTitle(R.string.action_settings);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        fetchDatabase();
        initListView();

    }


    private void initListView() {
        listView = (ListView) findViewById(R.id.listView);
        listView.setAdapter(new CellAdapter(getApplicationContext(), list));
    }

    private void fetchDatabase() {
        list = SessionEntity.listAll(SessionEntity.class);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        return true;
    }

}
