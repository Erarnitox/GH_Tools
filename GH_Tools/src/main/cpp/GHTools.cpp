#define __cplusplus 1

#include "./header/com_guidedhacking_GH_Tools_GHInput.h"
#include "./header/com_guidedhacking_GH_Tools_GHMemory.h"
#include "./header/com_guidedhacking_GH_Tools_GHTools.h"
#include "external.h"
#include <windows.h>

HANDLE hProcess = NULL;
bool openedGame = false;
int procIdGlob;

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_getGamePID(JNIEnv *, jclass){
	return procIdGlob;
}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_isGameVisible(JNIEnv *, jclass){
}

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_getGameHeight(JNIEnv *, jclass){
}

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_getGameWidth(JNIEnv *, jclass){
}

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_getGameXPos(JNIEnv *, jclass){
}

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHTools_getGameYPos(JNIEnv *, jclass){
}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_getKeyDown(JNIEnv*, jclass, jint) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_getKeyPress(JNIEnv*, jclass, jint) {

}

JNIEXPORT jint JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_getKeyPressed(JNIEnv*, jclass) {

}

JNIEXPORT void JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_sendKeyPress(JNIEnv*, jclass, jint) {

}

JNIEXPORT void JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_sendKeyDown(JNIEnv*, jclass, jint) {

}

JNIEXPORT void JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_sendKeyUp(JNIEnv*, jclass, jint) {

}

JNIEXPORT void JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_SetCursor(JNIEnv*, jclass, jint, jint) {

}

JNIEXPORT jintArray JNICALL Java_com_guidedhacking_GH_1Tools_GHInput_getCursorPos(JNIEnv*, jclass) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_openWindowName(JNIEnv*, jclass, jstring windowName, jobject) {
	
}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_openProcess(JNIEnv*, jclass, jstring s, jobject) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_isConnected(JNIEnv*, jclass) {
	return hProcess == INVALID_HANDLE_VALUE ? false : true;
}

JNIEXPORT jlong JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_getModuleBaseAddress__(JNIEnv*, jclass) {

}

JNIEXPORT jbyteArray JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_readMemory(JNIEnv*, jclass, jlong, jint) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_writeMemory(JNIEnv*, jclass, jlong, jbyteArray) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_patchMemory(JNIEnv*, jclass, jlong, jbyteArray) {

}

JNIEXPORT jboolean JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_nopMemory(JNIEnv*, jclass, jlong address, jint lenth) {
	NopExternal nop = new NopExternal();
}

JNIEXPORT jlong JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_getObjectAddress(JNIEnv*, jclass, jobject) {

}

JNIEXPORT void JNICALL Java_com_guidedhacking_GH_1Tools_GHMemory_close(JNIEnv*, jclass) {

}

