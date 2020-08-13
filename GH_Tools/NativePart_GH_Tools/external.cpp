#include "external.h"

DWORD GetProcId(const wchar_t* procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //create a snapshot of all currently running proceses
	if (hSnap != INVALID_HANDLE_VALUE) { //if taking a snapshot was successful
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) { //get the first process and place it in procEntry
			do {
				if (!_wcsicmp(procEntry.szExeFile, procName)) { //check if the name of this process matches the name of our game
					procId = procEntry.th32ProcessID; //if it matches save its process id in procId
					break; //break out of the loop
				}
			} while (Process32Next(hSnap, &procEntry)); //place the next process of the snapshot into procEntry (looping over each process in the snapshot)

		}
	}
	CloseHandle(hSnap); // "delete" our snapshot again
	return procId; //return the process id we have found 0 if we did not find our game
}

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId); //create a snapshot of all modules loaded by our game process
	if (hSnap != INVALID_HANDLE_VALUE) { //check if creating a snapshot was successful
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) { //place the first module in our snapshot in modEntry
			do {
				if (!_wcsicmp(modEntry.szModule, modName)) { //cheack if the module has the name of the module we are looking for
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr; //if we have found our module, save its address in modBaseAddr
					break; //break out of the loop
				}
			} while (Module32Next(hSnap, &modEntry)); //place the next module in the snapshot into modentry (looping over each module in the snapshot)
		}
	}
	CloseHandle(hSnap); // "delete" our snapshot
	return modBaseAddr; //return the address of the found module or 0 if we did not find it
}

inline uintptr_t FindDynamicAddress(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	for (unsigned int i = 0; i < offsets.size(); ++i) { //loop over the offsets
		ReadProcessMemory(hProc, (BYTE*)ptr, &ptr, sizeof(ptr), 0); //read memory at addr and save the result in addr
		ptr += offsets[i]; //add the current offset to addr
	}
	return ptr; //return the address the multi level pointer is pointing at currently
}

void PatchExternal(HANDLE hProcess, BYTE* dst, BYTE* src, size_t size) {
	DWORD oldprotect; //variable to hold a backup of our old protection
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect); //make memory writeable and save the old protection in oldprotect
	WriteProcessMemory(hProcess, dst, src, size, nullptr); //write the new opcodes to the target process and location
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect); //restore our old protection
}

NopExternal::NopExternal(HANDLE hProcess, BYTE* dst, size_t size)
	:hProcess{ hProcess }, dst{ dst }, size{ size }, originalCode{ new BYTE[size] }, nopCode{ new BYTE[size] } {
	memset(nopCode, 0x90, size); //initialize our nopCode
	ReadProcessMemory(hProcess, dst, originalCode, size, 0); //backup our original Code
}

void NopExternal::enable() { //enable our patch
	//write the code that does nothing to memory:
	PatchExternal(hProcess, dst, nopCode, size);
}

void NopExternal::disable() { //disable our patch
	//write the original code back to memory:
	PatchExternal(hProcess, dst, originalCode, size);
}

NopExternal::~NopExternal() { //clean up our patch object
	delete[] this->originalCode;
	delete[] this->nopCode;
}