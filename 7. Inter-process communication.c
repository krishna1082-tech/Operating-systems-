#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa;
    DWORD bytesWritten, bytesRead;
    char message[] = "Hello from parent process!";
    char buffer[100];

    // Set up security attributes to allow handle inheritance (not strictly needed here)
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = FALSE;

    // Create the pipe
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        fprintf(stderr, "Pipe creation failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Simulate parent writing to pipe
    if (!WriteFile(hWrite, message, strlen(message), &bytesWritten, NULL)) {
        fprintf(stderr, "Write to pipe failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Close the write end before reading (optional here, but good practice)
    CloseHandle(hWrite);

    // Simulate child reading from pipe
    if (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0'; // Null-terminate string
        printf("Child received: %s\n", buffer);
    } else {
        fprintf(stderr, "Read from pipe failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Clean up
    CloseHandle(hRead);

    return 0;
}
