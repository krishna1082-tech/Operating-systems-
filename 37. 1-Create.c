#include <windows.h>
#include <stdio.h>

DWORD WINAPI threadFunction(LPVOID lpParam) {
    printf("Inside the new thread\n");
    return 0;
}

int main() {
    HANDLE thread;
    DWORD threadId;

    // Create a new thread
    thread = CreateThread(
        NULL,           // default security attributes
        0,              // default stack size
        threadFunction, // thread function
        NULL,           // parameter to thread function
        0,              // default creation flags
        &threadId);     // receive thread identifier

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
