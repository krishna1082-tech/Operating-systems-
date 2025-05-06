#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();  // Create a new process

    if (pid == 0) {
        // Child process
        printf("This is the Child Process.\n");
    } else {
        // Parent process
        printf("This is the Parent Process.\n");
    }

    return 0;
}
