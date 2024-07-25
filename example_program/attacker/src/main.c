/*
	Copyright (c) 2024 SeanCodingThings/SeanProgramming
*/

#include "../../../src/sct-mem-api.h"
#include <stdio.h>

#define ADDRESS (uintptr_t)0xEE03FFE3C

static void print_error_and_exit(const char* message) {
    fprintf(stderr, "%s\n", message);
    getchar();
    exit(1);
}

int main(int argc, char** argv) {
    S_Process proc = sct_init_process("sct-test.exe");
    
    // Check if process initialization was successful
    if (proc.id == 0) {
        print_error_and_exit("Failed to find process, make sure it is opened!");
    }
    if (proc.handle == NULL) {
        print_error_and_exit("Failed to open the process with all access!");
    }
    if (proc.start_address == 0) {
        fprintf(stderr, "Failed to get the start address, this could be bad!\n");
    }

    printf("=== INFO ===\n");
    printf("Process name => \"%s\"\n", proc.name);
    printf("Process id => %d\n", proc.id);
    printf("Process start address => 0x%p\n", (void*)proc.start_address);

    // Read memory
    int buffer = 0;
    if (RPM(proc, ADDRESS, &buffer, sizeof(buffer)) != RPM_SUCCESS) {
        fprintf(stderr, "Failed to read memory at => 0x%p\n", (void*)ADDRESS);
    } else {
        printf("Value => %d\n", buffer);
    }
    int write_value = 1337;
    // Write memory
    if (WPM(proc, ADDRESS, &write_value, sizeof(int)) != WPM_SUCCESS) {
        fprintf(stderr, "Failed to write \"%d\" at => 0x%p\n", write_value, (void*)ADDRESS);
    }

    getchar(); // Wait for user input before exiting
    return 0;
}
