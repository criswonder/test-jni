package cookbook.testjni;

import android.opengl.EGL14;
import android.opengl.EGLContext;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;


public class MainActivity extends AppCompatActivity {
    private String TAG = "MainActivity";
    private boolean VERBOSE = true;

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


//        setFloatArray();

        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                float[] floats = new float[]{
//                        12f, 23f, 31f, 14f, 5f
//                };
//                float[] outFloats = setFloatArray(floats);
//                for (int i = 0; i < outFloats.length; i++) {
//                    Log.d("andymao", "" + outFloats[i]);
//                }

//                int[] intArray = new int[12];
//                try {
//                    getIntArray(intArray);
//                } catch (Throwable e) {
//                    e.printStackTrace();
//                }
//
//                for (int i = 0; i < intArray.length; i++) {
//                    Log.d("andymao", intArray[i] + "");
//                }

                EGLContext eglContext = testCPPCreateOpenGLContext(0);
                if(VERBOSE) Log.e(TAG,"onClick eglContext="+eglContext.getNativeHandle());
                EGLContext eglContext2 = testCPPCreateOpenGLContext(eglContext.getNativeHandle());
                if(VERBOSE) Log.e(TAG,"onClick eglContext="+eglContext2.getNativeHandle());
            }
        });

    }

    private EGLContext testCPPCreateOpenGLContext(final long eglContext) {
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        final EGLContext[] result = new EGLContext[1];
        Thread workThread = new Thread(new Runnable() {
            @Override
            public void run() {
                setNativeOpenglHandle(eglContext);
                result[0] = EGL14.eglGetCurrentContext();
                countDownLatch.countDown();
            }
        });
        workThread.start();
        try {
            countDownLatch.await(2000, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return result[0];
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
    public native float[] setFloatArray(float[] arrInput);

    public native void getIntArray(int[] intArrays);

    public native void setNativeOpenglHandle(long eglContext);
}
