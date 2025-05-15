#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa;
    DWORD bytesWritten, bytesRead;
    char message[] = "Hello from parent process!";
    char buffer[100];

    // Security attributes for the pipe
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = FALSE;

    // Create anonymous pipe
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        fprintf(stderr, "Pipe creation failed. Error: %lu\n", GetLastError());
        return 1;
    }

    // Parent writing to pipe
    if (!WriteFile(hWrite, message, strlen(message), &bytesWritten, NULL)) {
        fprintf(stderr, "Write to pipe failed. Error: %lu\n", GetLastError());
        return 1;
    }
    printf("Parent: Message sent to child.\n");

    CloseHandle(hWrite);  // Close write end

    // Child reading from pipe
    if (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';  // Null-terminate the string
        printf("Child: Received message = %s\n", buffer);
    } else {
        fprintf(stderr, "Read from pipe failed. Error: %lu\n", GetLastError());
        return 1;
    }

    CloseHandle(hRead);
    return 0;
}
