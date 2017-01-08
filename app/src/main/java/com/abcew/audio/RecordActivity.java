package com.abcew.audio;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

public class RecordActivity extends AppCompatActivity implements View.OnClickListener {

    static {
        System.loadLibrary("recorder-lib");
    }

    private boolean mRecording;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_record);

        findViewById(R.id.start).setOnClickListener(this);
        findViewById(R.id.stop).setOnClickListener(this);
        createEngine();
    }




    /** Native methods, implemented in jni folder */
    public native void createEngine();

    public native void createAudioRecord(String uri);

    public native void stop();

    public native void shutdown();

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.start:

                String path = Environment.getExternalStorageDirectory().toString()  + "/audio.pcm";
                Log.i("path",path);
                createAudioRecord(path);
                mRecording = true;
                break;
            case R.id.stop:
                stop();
                mRecording = false;
                break;
        }
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mRecording) {
            stop();
        }
        shutdown();
    }

}
