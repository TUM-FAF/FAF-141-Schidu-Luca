package com.example.schidu.pomodoro;

import android.os.CountDownTimer;
import android.util.Log;

import com.example.schidu.pomodoro.database.SessionEntity;
import java.util.GregorianCalendar;

/**
 * Created by schidu on 5/1/16.
 */
public class MainPresenter {

    private MainActivity view;
    CountDownTimer countDownTimer;
    int duration = 1500000;
    String elapsed;
    String time;
    int progress;


    public MainPresenter() {

        countDownTimer = new CountDownTimer(duration, 1000) {
            @Override
            public void onTick(long millisUntilFinished) {
                time = convertSecondsToHMmSs(millisUntilFinished/1000);
                elapsed = convertSecondsToHMmSs((duration - millisUntilFinished)/1000);
                progress = (int)(millisUntilFinished/(double)duration * 100);
                publish();
            }

            @Override
            public void onFinish() {

            }
        };
    }

    public void startTimer() {
        countDownTimer.cancel();
        countDownTimer.start();
    }

    public void stopTimer() {
        countDownTimer.cancel();
        SessionEntity entity = new SessionEntity(GregorianCalendar.getInstance().getTime().toString(), elapsed);
        entity.save();
        Log.e("Time dsadas", entity.getDate() + " " + entity.getDuration());
    }

    public static String convertSecondsToHMmSs(long seconds) {
        long s = seconds % 60;
        long m = (seconds / 60) % 60;
        return String.format("%02d:%02d", m,s);
    }

    public void onTakeView(MainActivity view) {
        this.view = view;
    }

    public void publish() {
        view.getData(time, progress);
    }
}
