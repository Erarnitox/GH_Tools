#include "../header/ghTools_GH.h"
#include <Windows.h>

INPUT input{};
HWND gameHandle;

JNIEXPORT jboolean JNICALL Java_ghTools_GH_getKeyDown(JNIEnv*, jclass, jint key) {
    return static_cast<bool>(GetAsyncKeyState(key));
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_getKeyPress(JNIEnv*, jclass, jint key) {
    return static_cast<bool>(GetAsyncKeyState(key) & 1);
}

   
JNIEXPORT jint JNICALL Java_ghTools_GH_getKeyPressed(JNIEnv*, jclass) {
    for (unsigned char i = 1; i < 0xFF; ++i) {
        if (GetAsyncKeyState(i)) return i;
    }
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyPress(JNIEnv*, jclass, jint key) {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT)); //key down

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT)); //key up
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyDown(JNIEnv*, jclass, jint key) {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT)); //key down
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyUp(JNIEnv*, jclass, jint key) {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT)); //key up
}

JNIEXPORT void JNICALL Java_ghTools_GH_setCursorPos(JNIEnv*, jclass, jint, jint) {
    
}

JNIEXPORT jintArray JNICALL Java_ghTools_GH_getCursorPos(JNIEnv* env, jclass) {
    POINT p;
    GetCursorPos(&p);
    jint jPos[2]{ p.x, p.y };
    jintArray pos{ env->NewIntArray(2) };
    env->SetIntArrayRegion( pos, 0, 2, jPos);
    return pos;
}

JNIEXPORT void JNICALL Java_ghTools_GH_setGameCursorPos(JNIEnv*, jclass, jint, jint) {

}

JNIEXPORT jintArray JNICALL Java_ghTools_GH_getGameCursorPos(JNIEnv* env, jclass) {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(gameHandle, &p);
    jint jPos[2]{ p.x, p.y };
    jintArray pos{ env->NewIntArray(2) };
    env->SetIntArrayRegion(pos, 0, 2, jPos);
    return pos;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_openWindowName(JNIEnv*, jclass, jstring) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_openProcess(JNIEnv*, jclass, jstring) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_isConnected(JNIEnv*, jclass) {

}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getModuleBaseAddress__(JNIEnv*, jclass) {

}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getModuleBaseAddress__Ljava_lang_String_2(JNIEnv*, jclass, jstring) {

}

JNIEXPORT jbyteArray JNICALL Java_ghTools_GH_readMemory(JNIEnv*, jclass, jlong, jint) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_writeMemory(JNIEnv*, jclass, jlong, jbyteArray) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_patchMemory(JNIEnv*, jclass, jlong, jbyteArray) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_nopMemory(JNIEnv*, jclass, jlong, jint) {

}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getObjectAddress(JNIEnv*, jclass, jobject) {

}

JNIEXPORT void JNICALL Java_ghTools_GH_close(JNIEnv*, jclass) {

}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGamePID(JNIEnv*, jclass) {

}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_isGameVisible(JNIEnv*, jclass) {

}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameHeight(JNIEnv*, jclass) {

}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameWidth(JNIEnv*, jclass) {

}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameXPos(JNIEnv*, jclass) {

}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameYPos(JNIEnv*, jclass) {

}

