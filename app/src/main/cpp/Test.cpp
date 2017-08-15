#include "Test.h"
#include "android/log.h"

Test::Test(int a,int b, int c){

}

Test::~Test(){}

void Test::setTransforamMatrix(float* fm){
    for(int i=0;i<2;i++){
        __android_log_print(ANDROID_LOG_ERROR,"andymao","setTransforamMatrix for loop item=%d,i=%d",*fm,i);
    }
}

