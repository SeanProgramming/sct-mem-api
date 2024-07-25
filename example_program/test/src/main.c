/*
	Copyright (c) 2024 SeanCodingThings/SeanProgramming
*/

#include <stdio.h>

int main(int argc, char** argv) {
    int value = 1000;
    char input;

    printf("=== TEST INFO ===\n");
    printf("Press 'q' to quit.\n");

    do {
        printf("\nVALUE ADDRESS => 0x%p\n", (void*)&value);
        printf("VALUE => %d\n", value);

        // Prompt user for input
        printf("Press 'q' to quit or any other key to continue: ");
        fflush(stdout);  // Ensure the prompt is printed immediately

        input = getchar();
        while (getchar() != '\n') ;  // Clear the newline character from the buffer

    } while (input != 'q' && input != 'Q');

    printf("Exiting...\n");
    return 0;
}
