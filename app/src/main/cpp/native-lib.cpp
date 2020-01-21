#include "native-lib.h"
#include "Test.h"
#include <jni.h>
#include <string>
#include "android/log.h"
#include <sys/system_properties.h>
#include <EGL/eglext.h>

extern "C"

//JNIEXPORT jstring JNICALL
//Java_cookbook_testjni_MainActivity_stringFromJNI(
//        JNIEnv* env,
//        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
//}


JNIEXPORT jfloatArray JNICALL
Java_cookbook_testjni_MainActivity_setFloatArray(
        JNIEnv *env,
        jobject thiz,
        jfloatArray fArray) {

//        jchar * stringSource = (jchar *)"abcdef";
////        const jchar * stringSource = "abcdef";
////        const jchar * stringSource = new jchar[]{'a','b','c','d','e'};
//        jstring jstring1 = env->NewString(stringSource,6);
//
//        jchar *jcharBuffer;
//        env->GetStringRegion(jstring1,0,3,jcharBuffer);

    int fLength = env->GetArrayLength(fArray);
    const float *floatArray = env->GetFloatArrayElements(fArray, 0);

    for (int i = 0; i < fLength; i++) {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "for loop item=%d,i=%d", *floatArray, i);
    }

    Test test(1, 3, 5);
    test.setTransforamMatrix(floatArray);

//        int aaa[5] = { 1, 2, 3, 4, 5};
//
//        for(int j=0;j<5;j++){
//            __android_log_print(ANDROID_LOG_ERROR,"andymao","for loop item=%d,j=%d",aaa[j],j);
//        }

    int newLength = fLength + 2;
    jfloatArray jfloatArray1 = env->NewFloatArray(newLength);
//        env->SetFloatArrayRegion(jfloatArray1,0,fLength,floatArray);

    return jfloatArray1;

}

//JNIEXPORT jfloatArray JNICALL Java_cookbook_testjni_JNIInterfaceTest_setFloatArray
//  (JNIEnv *, jobject, jfloatArray){
//
//
//
//  }
void fillIntArray(jint *&array) {
    jint *fkJintArray = new jint[12];
    for (int i = 0; i < 12; ++i) {
        fkJintArray[i] = i;
    }

    array = fkJintArray;
}
/**
 * http://androidxref.com/4.3_r2.1/xref/frameworks/base/opengl/java/android/opengl/EGLContext.java
 * http://androidxref.com/4.4_r1/xref/frameworks/base/opengl/java/android/opengl/EGLContext.java
 *
 * https://developer.android.com/reference/android/opengl/EGLObjectHandle.html#getHandle()
 * Use getNativeHandle() instead. Handles on 64 bit platforms will be wider than java ints.
 */
extern "C"
JNIEXPORT void JNICALL
Java_cookbook_testjni_MainActivity_getIntArray(JNIEnv *env, jobject instance,
                                               jintArray intArrays_) {
    // VERSION is a nested class within android.os.Build (hence "$" rather than "/")
    jclass versionClass = env->FindClass("android/os/Build$VERSION");
    jfieldID sdkIntFieldID = env->GetStaticFieldID(versionClass, "SDK_INT", "I");
    int sdkInt = env->GetStaticIntField(versionClass, sdkIntFieldID);
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "sdkInt %d", sdkInt);
    jclass eglcontextClassLocal = env->FindClass("android/opengl/EGLContext");
    jmethodID eglcontextConstructor;
    jobject eglContext;
    if (sdkInt >= 21) {
        //5.0and above
        eglcontextConstructor = env->GetMethodID(eglcontextClassLocal, "<init>", "(J)V");
        eglContext = env->NewObject(eglcontextClassLocal, eglcontextConstructor,
                                    reinterpret_cast<jlong>(jlong(10000)));
    } else {
        eglcontextConstructor = env->GetMethodID(eglcontextClassLocal, "<init>", "(I)V");
        eglContext = env->NewObject(eglcontextClassLocal, eglcontextConstructor,
                                    reinterpret_cast<jlong>(jlong(10000)));
    }


    jint *intArrays = env->GetIntArrayElements(intArrays_, NULL);

    fillIntArray(intArrays);

    env->ReleaseIntArrayElements(intArrays_, intArrays, 0);
}


//int api_version( struct android_app *app ) {
//
//    JNIEnv* env;
//    app->activity->vm->AttachCurrentThread( &env, NULL );
//
//    // VERSION is a nested class within android.os.Build (hence "$" rather than "/")
//    jclass versionClass = env->FindClass("android/os/Build$VERSION" );
//    jfieldID sdkIntFieldID = env->GetStaticFieldID(versionClass, "SDK_INT", "I" );
//
//    int sdkInt = env->GetStaticIntField(versionClass, sdkIntFieldID );
//    app->activity->vm->DetachCurrentThread();
//    return sdkInt;
//}



extern "C"
JNIEXPORT void JNICALL
Java_cookbook_testjni_MainActivity_setNativeOpenglHandle(JNIEnv *env, jobject thiz,
                                                         jlong egl_context) {
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "in jni");

    EGLContext *shareContext = NULL;
    unsigned long long egl_context1 = (unsigned long long) egl_context;
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "egl_context=%llu ",
                        egl_context1);
    if (egl_context1 > 0) {
        shareContext = (EGLContext *) egl_context;
    }

    EGLint numConfigs;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "EGL_NO_DISPLAY");
        return;
    }

    int eglVersionMajor;
    int eglVersionMinor;
    if (!eglInitialize(display, &eglVersionMajor, &eglVersionMinor)) {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "unable to initialize egl");
        return;
    }
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "egl version %d, %d"
            ,eglVersionMajor,eglVersionMinor);

    int attribList[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            //EGL_DEPTH_SIZE, 16,
            //EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };

    EGLConfig config = NULL;
    if (!eglChooseConfig(display, attribList, &config, 1, &numConfigs)) {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "choose config failed");
        return;
    }

    int surfaceAttribs[] = {
            EGL_WIDTH, 256,
            EGL_HEIGHT, 256,
            EGL_NONE
    };
    surface = eglCreatePbufferSurface(display, config, surfaceAttribs);

    // EGL context attributes
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,              // 初始化3.0的上下文
            EGL_NONE
    };
    context = eglCreateContext(display, config,
            shareContext != NULL ? shareContext : NULL, ctxAttr);

    int contextVersion;
    eglQueryContext(display, context, EGL_CONTEXT_CLIENT_VERSION, &contextVersion);
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "contextVersion %d",contextVersion);

//    eglQuerySurface(display, surface, EGL_WIDTH, &w);
//    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "eglMakeCurrent false");
    }else{
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "eglMakeCurrent true");
    }
}




