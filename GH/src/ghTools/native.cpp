#include "../header/ghTools_GH.h"
#include "../header/external.h"

INPUT keyboard{};
INPUT mouse{};
HWND gameWindow{ NULL };
HANDLE gameHandle{ NULL };
uintptr_t gameBase{ 0 };
DWORD procId{ 0 };

struct HandleData {
    DWORD pid;
    HWND hWnd;
};

BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam) {
    HandleData& data = *(HandleData*)lParam;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == data.pid && GetWindow(hWnd, GW_OWNER) == HWND(0) && IsWindowVisible(hWnd)) {
        data.hWnd = hWnd;
        return FALSE;
    }
    return TRUE;
}

HWND FindMainWindow(DWORD dwPID) {
    HandleData handleData{ 0 };
    handleData.pid = dwPID;
    EnumWindows(EnumWindowsCallback, (LPARAM)&handleData);
    return handleData.hWnd;
}

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
    return 0xff;
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyPress(JNIEnv*, jclass, jint key) {
    keyboard.type = INPUT_KEYBOARD;
    keyboard.ki.wVk = static_cast<WORD>(key);
    keyboard.ki.dwFlags = 0;
    SendInput(1, &keyboard, sizeof(INPUT)); //key down

    keyboard.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &keyboard, sizeof(INPUT)); //key up
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyDown(JNIEnv*, jclass, jint key) {
    keyboard.type = INPUT_KEYBOARD;
    keyboard.ki.wVk = static_cast<WORD>(key);
    keyboard.ki.dwFlags = 0;
    SendInput(1, &keyboard, sizeof(INPUT)); //key down
}

JNIEXPORT void JNICALL Java_ghTools_GH_sendKeyUp(JNIEnv*, jclass, jint key) {
    keyboard.type = INPUT_KEYBOARD;
    keyboard.ki.wVk = static_cast<WORD>(key);
    keyboard.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &keyboard, sizeof(INPUT)); //key up
}

JNIEXPORT void JNICALL Java_ghTools_GH_setCursorPos(JNIEnv*, jclass, jint x, jint y) {
    SetCursorPos(x, y);
}

JNIEXPORT jintArray JNICALL Java_ghTools_GH_getCursorPos(JNIEnv* env, jclass) {
    POINT p;
    GetCursorPos(&p);
    jint jPos[2]{ p.x, p.y };
    jintArray pos{ env->NewIntArray(2) };
    env->SetIntArrayRegion( pos, 0, 2, jPos);
    return pos;
}

JNIEXPORT void JNICALL Java_ghTools_GH_setGameCursorPos(JNIEnv*, jclass, jint x, jint y) {
    POINT p{ x,y };
    ScreenToClient(gameWindow, &p);
    SetCursorPos(p.x, p.y);
}

JNIEXPORT jintArray JNICALL Java_ghTools_GH_getGameCursorPos(JNIEnv* env, jclass) {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(gameWindow, &p);
    jint jPos[2]{ p.x, p.y };
    jintArray pos{ env->NewIntArray(2) };
    env->SetIntArrayRegion(pos, 0, 2, jPos);
    return pos;
}

JNIEXPORT void JNICALL Java_ghTools_GH_leftClick(JNIEnv*, jclass) {
    mouse.type = INPUT_MOUSE;
    mouse.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &mouse, sizeof(INPUT)); //mouse down
    mouse.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &mouse, sizeof(INPUT)); //mouse up
}

JNIEXPORT void JNICALL Java_ghTools_GH_rightClick(JNIEnv*, jclass) {
    mouse.type = INPUT_MOUSE;
    mouse.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &mouse, sizeof(INPUT)); //mouse down
    mouse.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &mouse, sizeof(INPUT)); //mouse up
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_openWindowName(JNIEnv* env, jclass, jstring windowName) {
    const wchar_t* winName{ (wchar_t*) env->GetStringUTFChars(windowName, 0) };
    gameWindow = FindWindow(NULL, winName);
    GetWindowThreadProcessId(gameWindow, &procId);
    gameBase = GetModuleBaseAddress(procId, NULL);
    gameHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

    if (gameHandle) return true;
    else return false;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_openProcess(JNIEnv* env, jclass, jstring processName) {
    const wchar_t* winName{ (wchar_t*)env->GetStringUTFChars(processName, 0) };
    procId = GetProcId(winName);
    gameBase = GetModuleBaseAddress(procId, NULL);
    gameHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    gameWindow = FindMainWindow(procId);

    if (gameHandle) return true;
    else return false;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_isConnected(JNIEnv*, jclass) {
    return (gameHandle == NULL) || (gameHandle == INVALID_HANDLE_VALUE) ? false : true;
}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getModuleBaseAddress__(JNIEnv*, jclass) {
    return gameBase;
}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getModuleBaseAddress__Ljava_lang_String_2(JNIEnv* env, jclass, jstring moduleName) {
    const wchar_t* modName{ (wchar_t*)env->GetStringUTFChars(moduleName, 0) };
    return GetModuleBaseAddress(procId, modName);
}

JNIEXPORT jbyteArray JNICALL Java_ghTools_GH_readMemory(JNIEnv* env, jclass, jlong address, jint length) {
    jbyte* byteArray = (jbyte*)_malloca(length);
    if (!byteArray) return nullptr;
    ReadProcessMemory(gameHandle, (LPVOID)address, byteArray, length, NULL);
    jbyteArray read{ env->NewByteArray(length) };
    env->SetByteArrayRegion(read, 0, length, byteArray);
    _freea(byteArray);
    return read;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_writeMemory(JNIEnv* env, jclass, jlong address, jbyteArray bytesToWrite) {
    SIZE_T written;
    SIZE_T len{ (size_t) env->GetArrayLength(bytesToWrite) };
    WriteProcessMemory(gameHandle, (LPVOID) address, env->GetByteArrayElements(bytesToWrite, NULL), len,  &written);
    return (written == len) ? true : false;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_patchMemory(JNIEnv* env, jclass, jlong address, jbyteArray bytesToWrite) {
    SIZE_T written;
    DWORD oldprotect;
    SIZE_T len{ (size_t) env->GetArrayLength(bytesToWrite) };
    VirtualProtectEx(gameHandle, (LPVOID) address, len, PAGE_EXECUTE_READWRITE, &oldprotect);
    WriteProcessMemory(gameHandle, (LPVOID) address, env->GetByteArrayElements(bytesToWrite, NULL), len, &written);
    VirtualProtectEx(gameHandle, (LPVOID) address, len, oldprotect, &oldprotect);
    return (written == len) ? true : false;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_nopMemory(JNIEnv*, jclass, jlong address, jint length) {
    jint written;
    DWORD oldprotect;
    char* nopBytes{ (char*)_malloca(length) };
    if (nopBytes){
        memset(nopBytes, 0x90, length);
        VirtualProtectEx(gameHandle, (LPVOID)address, length, PAGE_EXECUTE_READWRITE, &oldprotect);
        WriteProcessMemory(gameHandle, (LPVOID)address, nopBytes, length, (SIZE_T*)&written);
        VirtualProtectEx(gameHandle, (LPVOID)address, length, oldprotect, &oldprotect);
        _freea(nopBytes);
        return (written == length) ? true : false;
    }
    return false;
}

JNIEXPORT jlong JNICALL Java_ghTools_GH_getObjectAddress(JNIEnv* env, jclass cls, jobject ghPointer) {
    jfieldID fidLong{ env->GetFieldID(cls, "staticPointer", "J") };
    jlong address{ env->GetLongField(ghPointer, fidLong) };

    jfieldID fidInt{env->GetFieldID(cls, "offsets", "[I")};
    jobject offsetsObject{ env->GetObjectField(ghPointer, fidInt) };
    jintArray* offsets = reinterpret_cast<jintArray*>(&offsetsObject);
    unsigned* start{ reinterpret_cast<unsigned*>(env->GetIntArrayElements(*offsets, NULL)) };
    std::vector<unsigned int> offsetsVector(start, start+env->GetArrayLength(*offsets));
    
    for (unsigned int i = 0; i < offsetsVector.size(); ++i) { 
        ReadProcessMemory(gameHandle, (BYTE*)address, &address, sizeof(address), 0);
        address += offsetsVector[i]; 
    }
    env->ReleaseIntArrayElements(*offsets, env->GetIntArrayElements(*offsets, NULL), NULL);
    return address;
}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGamePID(JNIEnv*, jclass) {
    return procId;
}

JNIEXPORT jboolean JNICALL Java_ghTools_GH_isGameVisible(JNIEnv*, jclass) {
    return IsWindowVisible(gameWindow);
}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameHeight(JNIEnv*, jclass) {
    RECT rect;
    GetWindowRect(gameWindow, &rect);
    return (rect.bottom - rect.top);
}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameWidth(JNIEnv*, jclass) {
    RECT rect;
    GetWindowRect(gameWindow, &rect);
    return (rect.right - rect.left);
}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameXPos(JNIEnv*, jclass) {
    RECT rect;
    GetWindowRect(gameWindow, &rect);
    return rect.left;
}

JNIEXPORT jint JNICALL Java_ghTools_GH_getGameYPos(JNIEnv*, jclass) {
    RECT rect;
    GetWindowRect(gameWindow, &rect);
    return rect.top;
}

