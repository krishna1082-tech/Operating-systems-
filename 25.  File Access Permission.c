#include <stdio.h>
#include <string.h>

// Structure to represent file permissions
typedef struct {
    char filename[100];
    int owner[3];  // 0: read, 1: write, 2: execute
    int group[3];
    int others[3];
} File;

void displayPermissions(File file) {
    printf("\nPermissions for file: %s\n", file.filename);
    printf("Owner  : %c%c%c\n",
           file.owner[0] ? 'r' : '-',
           file.owner[1] ? 'w' : '-',
           file.owner[2] ? 'x' : '-');
    printf("Group  : %c%c%c\n",
           file.group[0] ? 'r' : '-',
           file.group[1] ? 'w' : '-',
           file.group[2] ? 'x' : '-');
    printf("Others : %c%c%c\n",
           file.others[0] ? 'r' : '-',
           file.others[1] ? 'w' : '-',
           file.others[2] ? 'x' : '-');
}

void changePermission(int *perm, const char *type) {
    printf("Set permissions for %s (0 = No, 1 = Yes):\n", type);
    printf("Read? "); scanf("%d", &perm[0]);
    printf("Write? "); scanf("%d", &perm[1]);
    printf("Execute? "); scanf("%d", &perm[2]);
}

int main() {
    File file;

    strcpy(file.filename, "example_windows.txt");

    // Set default permissions
    file.owner[0] = 1; file.owner[1] = 1; file.owner[2] = 0;    // rw-
    file.group[0] = 1; file.group[1] = 0; file.group[2] = 0;    // r--
    file.others[0] = 0; file.others[1] = 0; file.others[2] = 0; // ---

    displayPermissions(file);

    // Let user modify permissions
    printf("\n--- Modify Permissions ---\n");
    changePermission(file.owner, "Owner");
    changePermission(file.group, "Group");
    changePermission(file.others, "Others");

    // Show updated permissions
    displayPermissions(file);

    return 0;
}
