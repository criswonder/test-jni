#include "native-lib.h"
#include "Test.h"
#include <jni.h>
#include <string>
#include "android/log.h"
#include <sys/system_properties.h>

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
void fillIntArray(jint*& array) {
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
    __android_log_print(ANDROID_LOG_ERROR, "andymao", "111");
    jclass eglcontextClassLocal = env->FindClass("android/opengl/EGLContext");
    jmethodID eglcontextConstructor;
    jobject jobject1;
    try {
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "xxxx");
        eglcontextConstructor=env->GetMethodID(eglcontextClassLocal, "<init>", "(J)V");
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "xxxx222");
        jobject1 = env->NewObject(eglcontextClassLocal, eglcontextConstructor,
                                          reinterpret_cast<jlong>(jlong(10000)));
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "333");
    }catch (...){
        __android_log_print(ANDROID_LOG_ERROR, "andymao", "111--->111");
        eglcontextConstructor=env->GetMethodID(eglcontextClassLocal, "<init>", "(I)V");
        jobject1 = env->NewObject(eglcontextClassLocal, eglcontextConstructor,
                                          reinterpret_cast<jlong>(jlong(10000)));
    }

    __android_log_print(ANDROID_LOG_ERROR, "andymao", "222");



    __android_log_print(ANDROID_LOG_ERROR, "andymao", "kkkkkkkk");

    jint *intArrays = env->GetIntArrayElements(intArrays_, NULL);

    fillIntArray(intArrays);

    env->ReleaseIntArrayElements(intArrays_, intArrays, 0);
}



