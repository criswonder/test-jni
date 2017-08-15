package cookbook.testjni;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());

        float[] floats = new float[]{
                12f, 23f, 31f, 14f, 5f
        };

//        setFloatArray();

        float[] outFloats = setFloatArray(floats);
        for (int i = 0; i < outFloats.length; i++) {
            Log.d("andymao", "" + outFloats[i]);
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();

    public native float[] setFloatArray(float[] arrInput);
}
