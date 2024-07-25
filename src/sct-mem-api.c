/*
	Copyright (c) 2024 SeanCodingThings/SeanProgramming
*/

#include "sct-mem-api.h"
#include <tlhelp32.h>
#include <string.h>

uintptr_t get_module_start_address(S_Process proc, const char* module_name) {
	MODULEENTRY32 entry = {0};
	entry.dwSize = sizeof(MODULEENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proc.id);
	Module32First(snapshot, &entry);
	do {
		if(strcmp(entry.szModule, module_name) == 0) {break;}
	} while(Module32Next(snapshot, &entry));
	CloseHandle(snapshot);
	return (uintptr_t)entry.modBaseAddr;
}
uintptr_t follow_pointer_chain(S_Process proc, uintptr_t start_address, uint64_t offsets[], int size_offsets) {
	const int num_offsets = size_offsets/sizeof(offsets[0]);
	uintptr_t address = start_address;
	for (int i = 0; i < num_offsets; i++) {
		if(RPM(proc, (address + offsets[num_offsets]), &address, sizeof(address)) != RPM_SUCCESS) return 0;
	}
	return address;
}

int RPM(S_Process proc, uintptr_t address, void* buffer, size_t size) {
    DWORD old_protect = 0;
    DWORD old_old_protect = 0;
    if (!VirtualProtectEx(proc.handle, (void*)address, size, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return RPM_ERROR_PROTECTION;
	}
    if (!ReadProcessMemory(proc.handle, (const void*)address, buffer, size, NULL)) {
        VirtualProtectEx(proc.handle, (void*)address, size, old_protect, &old_old_protect);
        return RPM_ERROR_READ;
    }
    VirtualProtectEx(proc.handle, (void*)address, size, old_protect, &old_old_protect);
    return RPM_SUCCESS;
}
int WPM(S_Process proc, uintptr_t address, void* value, size_t value_size) {
	DWORD old_protect = 0;
	DWORD old_old_protect = 0;
	if (!VirtualProtectEx(proc.handle, (void*)address, value_size, PAGE_EXECUTE_READWRITE, &old_protect)) {
		return WPM_ERROR_PROTECTION;
	}
	if(!WriteProcessMemory(proc.handle, (void*)address, value, value_size, NULL)) {
		VirtualProtectEx(proc.handle, (void*)address, value_size, old_protect, &old_old_protect);
		return WPM_ERROR_WRITE;
	}
	VirtualProtectEx(proc.handle, (void*)address, sizeof(address), old_protect, &old_old_protect);
	return 0;
}


static int get_pid(const char* process_name) {
	PROCESSENTRY32 entry = {0};
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(snapshot, &entry);
	do {
		if(strcmp(entry.szExeFile, process_name) == 0) {break;}
	} while(Process32Next(snapshot, &entry) == TRUE);
	CloseHandle(snapshot);
	return entry.th32ProcessID;
}

S_Process sct_init_process(const char* process_name) {
	S_Process proc = {
		.name = process_name,
		.id = 0,
		.handle = NULL,
		.start_address = 0
	};
	proc.id = get_pid(proc.name);
	proc.handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc.id);
	proc.start_address = get_module_start_address(proc, proc.name);
	return proc;
}