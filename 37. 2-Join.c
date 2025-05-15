#include <windows.h>
#include <stdio.h>

// Thread function
DWORD WINAPI threadFunction(LPVOID lpParam) {
    printf("Inside the new thread\n");
    return 0;
}

int main() {
    HANDLE threadHandle;
    DWORD threadId;

    // Create a new thread
    threadHandle = CreateThread(
        NULL,
        0,
        threadFunction,
        NULL,
        0,
        &threadId
    );

    if (threadHandle == NULL) {
        fprintf(stderr, "Failed to create thread\n");
        return 1;
    }

    printf("Inside the main thread\n");

    // Wait for the thread to finish
    WaitForSingleObject(threadHandle, INFINITE);

    printf("Main thread: Joined the new thread\n");

    // Close thread handle
    CloseHandle(threadHandle);

    printf("Press Enter to exit...");
    getchar();  // Pause so console window stays open

    return 0;
}
