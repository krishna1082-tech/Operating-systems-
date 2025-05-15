#include <windows.h>
#include <stdio.h>

HANDLE hMutex; // Global handle to the mutex

// Thread function
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    int threadNum = (int)(SIZE_T)lpParam; // Correct cast to get thread number

    for (int i = 0; i < 3; i++) {
        // Request ownership of the mutex
        WaitForSingleObject(hMutex, INFINITE);

        // Begin of critical section
        printf("Thread %d is in the critical section (iteration %d).\n", threadNum, i + 1);
        Sleep(1000); // Simulate critical section work
        printf("Thread %d is leaving the critical section.\n", threadNum);
        // End of critical section

        // Release ownership of the mutex
        ReleaseMutex(hMutex);

        Sleep(500); // Simulate work outside the critical section
    }

    return 0;
}

int main() {
    HANDLE hThreads[2];

    // Create a mutex with default security attributes, not owned initially
    hMutex = CreateMutex(NULL, FALSE, NULL);
    if (hMutex == NULL) {
        printf("CreateMutex failed with error: %lu\n", GetLastError());
        return 1;
    }

    // Create two threads
    for (int i = 0; i < 2; i++) {
        hThreads[i] = CreateThread(
            NULL,              // Default security attributes
            0,                 // Default stack size
            ThreadFunction,    // Thread function
            (LPVOID)(SIZE_T)(i + 1), // Pass thread number as parameter
            0,                 // Default creation flags
            NULL               // No thread ID
        );

        if (hThreads[i] == NULL) {
            printf("CreateThread failed with error: %lu\n", GetLastError());
            return 1;
        }
    }

    // Wait for both threads to finish
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    // Close thread and mutex handles
    for (int i = 0; i < 2; i++) {
        CloseHandle(hThreads[i]);
    }
    CloseHandle(hMutex);

    printf("All threads have finished execution.\n");

    return 0;
}
