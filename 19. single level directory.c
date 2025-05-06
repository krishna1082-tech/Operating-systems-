#include <stdio.h>
#include <string.h>

#define MAX 100

struct File {
    char name[20];
} directory[MAX];

int fileCount = 0;

void createFile() {
    if (fileCount >= MAX) {
        printf("Directory is full!\n");
        return;
    }

    char filename[20];
    printf("Enter the name of the file to create: ");
    scanf("%s", filename);

    // Check for duplicate
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(directory[fileCount].name, filename);
    fileCount++;
    printf("File created successfully.\n");
}

void deleteFile() {
    char filename[20];
    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            // Shift files left
            for (int j = i; j < fileCount - 1; j++) {
                strcpy(directory[j].name, directory[j + 1].name);
            }
            fileCount--;
            printf("File deleted successfully.\n");
            return;
        }
    }

    printf("File not found.\n");
}

void searchFile() {
    char filename[20];
    printf("Enter the name of the file to search: ");
    scanf("%s", filename);

    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File found.\n");
            return;
        }
    }

    printf("File not found.\n");
}

void displayFiles() {
    if (fileCount == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Files in directory:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s\n", directory[i].name);
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Single-Level Directory Menu ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
