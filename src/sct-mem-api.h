/*
	Copyright (c) 2024 SeanCodingThings/SeanProgramming
*/

#ifndef SCT_MEM_API_H
#define SCT_MEM_API_H

#include <Windows.h>
#include <stdint.h>

typedef struct S_Process {
	const char* name;
	int id;
	HANDLE handle;
	uintptr_t start_address;
}S_Process;

/*
	get_module_start_address: Gets the address of a module (.dll) inside of a process (.exe)

	@proc: A valid S_Process structure that was passed in the function sct_init_process

	@module_name: The name of the module including the .dll extension.

	@return: The module address, or 0 on failure.
*/
extern uintptr_t get_module_start_address(S_Process proc, const char* module_name);
/*
	follow_pointer_chain: Follows a pointer chain with offsets.

	@proc: A valid S_Process structure that was passed in the function sct_init_process

	@start_address: The start address of the chain.

	@offsets: An array of offsets between each address (The array is used to determine how long is the chain.)

	@size_offsets: sizeof(offsets) (The size of the array in bytes.)

	@return: The module address, or 0 on failure.
*/
extern uintptr_t follow_pointer_chain(S_Process proc, uintptr_t start_address, uint64_t offsets[], int size_offsets);


#define RPM_SUCCESS 0
#define RPM_ERROR_PROTECTION 1
#define RPM_ERROR_READ 2
/*
	RPM: Reads memory in proc from an address in a safe maner.

	@proc: A valid S_Process structure that was passed in the function sct_init_process.

	@address: The address to read a value from.

	@buffer: the address of the where to store the value read.

	@size: the size in bytes of the buffer (sizeof(type))

	@return: On of the RPM macros:
	RPM_SUCCESS 0
	RPM_ERROR_PROTECTION 1
	RPM_ERROR_READ 2
*/
extern int RPM(S_Process proc, uintptr_t address, void* buffer, size_t size);
#define WPM_SUCCESS 0
#define WPM_ERROR_PROTECTION 1
#define WPM_ERROR_WRITE 2
/*
	WPM: Writes to memory in proc to an address in a safe maner.

	@proc: A valid S_Process structure that was passed in the function sct_init_process.

	@address: The address to write the value to.

	@value: The address of the value to write to the address.

	@value_size: The size in bytes of the value (sizeof(type))

	@return: On of the WPM macros:
	WPM_SUCCESS 0
	WPM_ERROR_PROTECTION 1
	WPM_ERROR_WRITE 2
*/
extern int WPM(S_Process proc, uintptr_t address, void* value, size_t value_size);

/*
	sct_init_process: Creates a new S_Process and assigns correct values to it.

	@process_name: the name of the process to get info from including the .exe extension.

	@return: The process created.

	@Extra info:
	In the new S_Process, the id will be set to 0 if the process was either not found or there was an error,
	The handle will be set to NULL and the start_address will be 0.
*/
extern S_Process sct_init_process(const char* process_name);

#endif