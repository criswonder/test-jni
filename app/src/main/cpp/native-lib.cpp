#include "native-lib.h"
#include "Test.h"
#include <jni.h>
#include <string>
#include "android/log.h"
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
        JNIEnv * env,
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
        const float * floatArray = env->GetFloatArrayElements(fArray,0);

        for(int i=0;i<fLength;i++){
            __android_log_print(ANDROID_LOG_ERROR,"andymao","for loop item=%d,i=%d",*floatArray,i);
        }

        Test test(1,3,5);
        test.setTransforamMatrix(floatArray);

//        int aaa[5] = { 1, 2, 3, 4, 5};
//
//        for(int j=0;j<5;j++){
//            __android_log_print(ANDROID_LOG_ERROR,"andymao","for loop item=%d,j=%d",aaa[j],j);
//        }

        int newLength = fLength+2;
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

