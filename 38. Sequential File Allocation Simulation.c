#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define RECORD_SIZE 100

typedef struct {
    int recordNumber;
    char data[RECORD_SIZE];
} Record;

typedef struct {
    char fileName[50];
    Record records[MAX_RECORDS];
    int recordCount;
} File;

// Function to create a new file
void createFile(File *file, const char *name) {
    strcpy(file->fileName, name);
    file->recordCount = 0;
    printf("File '%s' created.\n", file->fileName);
}

// Add a record to the file
void addRecord(File *file, const char *data) {
    if (file->recordCount >= MAX_RECORDS) {
        printf("File is full. Cannot add more records.\n");
        return;
    }

    file->records[file->recordCount].recordNumber = file->recordCount + 1;
    strncpy(file->records[file->recordCount].data, data, RECORD_SIZE);
    file->recordCount++;

    printf("Record added to file '%s'.\n", file->fileName);
}

// Read a record sequentially
void readRecordSequentially(File *file, int recordNumber) {
    if (recordNumber > file->recordCount || recordNumber < 1) {
        printf("Invalid record number.\n");
        return;
    }

    printf("\nReading records sequentially up to record %d:\n", recordNumber);
    for (int i = 0; i < recordNumber; i++) {
        printf("Record %d: %s\n", file->records[i].recordNumber, file->records[i].data);
    }
}

// Driver code
int main() {
    File myFile;

    createFile(&myFile, "student_data");

    // Adding some records
    addRecord(&myFile, "Alice - Roll No 1");
    addRecord(&myFile, "Bob - Roll No 2");
    addRecord(&myFile, "Charlie - Roll No 3");

    int recordToRead;
    printf("\nEnter the record number to read (sequential access): ");
    scanf("%d", &recordToRead);

    readRecordSequentially(&myFile, recordToRead);

    return 0;
}
