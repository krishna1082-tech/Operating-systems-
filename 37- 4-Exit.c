#include <stdio.h>
#include <windows.h>

// Thread function
DWORD WINAPI threadFunction(LPVOID arg) {
    printf("Inside the new thread\n");
    return 0;
}

int main() {
    HANDLE thread;
    DWORD threadId;

    // Create a new thread
    thread = CreateThread(
        NULL,          // Default security attributes
        0,             // Default stack size
        threadFunction,// Thread function
        NULL,          // Argument to thread function
        0,             // Default creation flags
        &threadId      // Returns the thread identifier
    );

    if (thread == NULL) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    printf("Inside the main thread\n");

    // Wait for the created thread to finish
    WaitForSingleObject(thread, INFINITE);

    // Close the thread handle
    CloseHandle(thread);

    return 0;
}
