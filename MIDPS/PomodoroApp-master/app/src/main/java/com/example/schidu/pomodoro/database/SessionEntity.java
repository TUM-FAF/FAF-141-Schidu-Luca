package com.example.schidu.pomodoro.database;

import com.orm.SugarRecord;

/**
 * Created by schidu on 5/2/16.
 */
public class SessionEntity extends SugarRecord {

    String date;
    String duration;


    public SessionEntity() {}

    public SessionEntity(String date, String duration) {
        this.date = date;
        this.duration = duration;
    }

    public String getDate() {
        return date;
    }

    public String getDuration() {
        return duration;
    }


}
