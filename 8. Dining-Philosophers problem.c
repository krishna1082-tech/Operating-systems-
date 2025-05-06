#include <windows.h>
#include <stdio.h>

#define NUM_PHILOSOPHERS 5

CRITICAL_SECTION forks[NUM_PHILOSOPHERS];

DWORD WINAPI philosopher(LPVOID arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    printf("Philosopher %d is thinking...\n", id);
    Sleep(1000);

    // Avoid deadlock: even IDs pick left first, odd pick right first
    if (id % 2 == 0) {
        EnterCriticalSection(&forks[left]);
        EnterCriticalSection(&forks[right]);
    } else {
        EnterCriticalSection(&forks[right]);
        EnterCriticalSection(&forks[left]);
    }

    printf("Philosopher %d is eating...\n", id);
    Sleep(1500);

    LeaveCriticalSection(&forks[left]);
    LeaveCriticalSection(&forks[right]);

    printf("Philosopher %d has finished eating and left the table.\n", id);
    return 0;
}

int main() {
    HANDLE threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        InitializeCriticalSection(&forks[i]);
    }

    // Start philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        threads[i] = CreateThread(NULL, 0, philosopher, &ids[i], 0, NULL);
    }

    // Wait for all to finish
    WaitForMultipleObjects(NUM_PHILOSOPHERS, threads, TRUE, INFINITE);

    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        DeleteCriticalSection(&forks[i]);
        CloseHandle(threads[i]);
    }

    printf("\nAll philosophers have finished. Program exiting.\n");
    return 0;
}
