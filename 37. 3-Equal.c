#include <stdio.h>
#include <windows.h>

// Thread function
DWORD WINAPI threadFunction(LPVOID arg) {
    printf("Inside the new thread\n");
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    DWORD threadId1, threadId2;

    // Create two threads
    thread1 = CreateThread(NULL, 0, threadFunction, NULL, 0, &threadId1);
    thread2 = CreateThread(NULL, 0, threadFunction, NULL, 0, &threadId2);

    if (thread1 == NULL || thread2 == NULL) {
        fprintf(stderr, "Error creating threads\n");
        return 1;
    }

    // Check if the threads are equal (comparing handles)
    if (thread1 == thread2) {
        printf("Threads are equal (same handle)\n");
    } else {
        printf("Threads are not equal (different handles)\n");
    }

    // Wait for both threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}
