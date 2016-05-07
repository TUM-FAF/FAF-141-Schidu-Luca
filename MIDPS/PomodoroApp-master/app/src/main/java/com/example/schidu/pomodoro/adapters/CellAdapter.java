package com.example.schidu.pomodoro.adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;


import com.example.schidu.pomodoro.R;
import com.example.schidu.pomodoro.database.SessionEntity;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by schidu on 5/2/16.
 */
public class CellAdapter extends BaseAdapter {

    private Context context;
    private List<SessionEntity> list;

    public CellAdapter(Context context, List<SessionEntity> list){
        this.context = context;
        this.list = list;
    }


        @Override
        public int getCount() {
            return list.size();
        }

        @Override
        public Object getItem(int position) {
            return list.get(position);
        }

        @Override
        public long getItemId(int position) {
            return 0;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {

            if (convertView == null) {
                LayoutInflater inflater = (LayoutInflater) context
                        .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
                convertView = inflater.inflate(R.layout.cell_adapter_layout, null);

            }

            TextView dateTextview = (TextView) convertView.findViewById(R.id.dateTextView);
            TextView durationTextView = (TextView) convertView.findViewById(R.id.durationTextView);

            dateTextview.setText(list.get(position).getDate());
            durationTextView.setText(list.get(position).getDuration());

            return convertView;
        }
    }

