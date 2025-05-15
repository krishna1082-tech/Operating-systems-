#include <windows.h>
#include <stdio.h>

int shared = 1;        // Shared variable
HANDLE mutex;          // Mutex handle

DWORD WINAPI fun1(LPVOID lpParam) {
    int x;

    WaitForSingleObject(mutex, INFINITE);  // Lock mutex
    x = shared;
    printf("Thread1 reads the value as %d\n", x);

    x++;
    printf("Local updation by Thread1: %d\n", x);

    Sleep(1000);  // Sleep for 1 second (simulate preemption)

    shared = x;
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    ReleaseMutex(mutex);  // Unlock mutex
    return 0;
}

DWORD WINAPI fun2(LPVOID lpParam) {
    int y;

    WaitForSingleObject(mutex, INFINITE);
    y = shared;
    printf("Thread2 reads the value as %d\n", y);

    y--;
    printf("Local updation by Thread2: %d\n", y);

    Sleep(1000);

    shared = y;
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    ReleaseMutex(mutex);
    return 0;
}

int main() {
    HANDLE t1, t2;

    mutex = CreateMutex(NULL, FALSE, NULL);  // Create an unnamed mutex

    if (mutex == NULL) {
        printf("CreateMutex error: %lu\n", GetLastError());
        return 1;
    }

    t1 = CreateThread(NULL, 0, fun1, NULL, 0, NULL);
    t2 = CreateThread(NULL, 0, fun2, NULL, 0, NULL);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(t1);
    CloseHandle(t2);
    CloseHandle(mutex);

    return 0;
}
