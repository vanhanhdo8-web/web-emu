//
// Created by 15874 on 2024/8/9.
//
#include "vibration.h"
#ifdef __ANDROID__
#include <SDL.h>
#include <jni.h>

void Vibration::vibrate(long milliseconds) {
    JNIEnv* env = (JNIEnv*)SDL_AndroidGetJNIEnv();
    if (env == NULL) return;
    jclass activityClass = env->FindClass("com/tele/u8emulator/Game");
    if (activityClass == NULL) return;
    jmethodID vibrateMethod = env->GetStaticMethodID(activityClass, "nativeVibrate", "(J)V");
    if (vibrateMethod == NULL) return;
    env->CallStaticVoidMethod(activityClass, vibrateMethod, (jlong)milliseconds);
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_tele_u8emulator_Game_nativeVibrate(JNIEnv* env, jclass cls, jlong milliseconds) {
        jclass activityClass = env->FindClass("com/tele/u8emulator/Game");
        if (activityClass == NULL) return;
        jmethodID vibrateMethod = env->GetStaticMethodID(activityClass, "nativeVibrate", "(J)V");
        if (vibrateMethod == NULL) return;
        env->CallStaticVoidMethod(activityClass, vibrateMethod, milliseconds);
    }
}
#elif defined(__EMSCRIPTEN__)
#include <emscripten.h>
void Vibration::vibrate(long milliseconds) {
    EM_ASM({ if (navigator.vibrate) navigator.vibrate($0); }, (int)milliseconds);
}
#else
void Vibration::vibrate(long milliseconds) {
    (void)milliseconds;
}
#endif
