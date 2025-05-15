#include <windows.h>
#include <stdio.h>

int sharedData = 0;
int readerCount = 0;

HANDLE mutexReaderCount;
HANDLE resourceMutex;

DWORD WINAPI Reader(LPVOID param) {
    int id = *((int*)param);

    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(mutexReaderCount, INFINITE);
        readerCount++;
        if (readerCount == 1) {
            WaitForSingleObject(resourceMutex, INFINITE);
        }
        ReleaseMutex(mutexReaderCount);

        printf("Reader %d reads sharedData = %d\n", id, sharedData);
        Sleep(1000);

        WaitForSingleObject(mutexReaderCount, INFINITE);
        readerCount--;
        if (readerCount == 0) {
            ReleaseMutex(resourceMutex);
        }
        ReleaseMutex(mutexReaderCount);

        Sleep(1500);
    }
    return 0;
}

DWORD WINAPI Writer(LPVOID param) {
    int id = *((int*)param);

    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(resourceMutex, INFINITE);

        sharedData++;
        printf("Writer %d writes sharedData = %d\n", id, sharedData);
        Sleep(1000);

        ReleaseMutex(resourceMutex);

        Sleep(2000);
    }
    return 0;
}

int main() {
    HANDLE readerThread, writerThread;
    int readerID = 1, writerID = 1;

    mutexReaderCount = CreateMutex(NULL, FALSE, NULL);
    resourceMutex = CreateMutex(NULL, FALSE, NULL);

    readerThread = CreateThread(NULL, 0, Reader, &readerID, 0, NULL);
    writerThread = CreateThread(NULL, 0, Writer, &writerID, 0, NULL);

    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);

    CloseHandle(mutexReaderCount);
    CloseHandle(resourceMutex);
    CloseHandle(readerThread);
    CloseHandle(writerThread);

    printf("Finished!\n");
    return 0;
}
