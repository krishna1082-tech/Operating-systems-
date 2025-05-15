#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

void addRecord(FILE *file) {
    struct Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.empId);

    // Check if the Employee ID already exists
    fseek(file, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, file) == 1 && emp.empId == emp.empId) {
        printf("Error: Employee with ID %d already exists.\n", emp.empId);
        return;
    }

    // Enter Employee details
    printf("Enter Employee Name: ");
    getchar(); // To consume the newline left by the previous input
    fgets(emp.empName, sizeof(emp.empName), stdin);
    emp.empName[strcspn(emp.empName, "\n")] = '\0';  // Remove the trailing newline

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);

    // Write the record to the file
    fseek(file, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Record added successfully!\n");
}

void displayAllRecords(FILE *file) {
    struct Employee emp;
    rewind(file);

    printf("\nEmployee Records:\n");
    printf("ID\tName\t\tSalary\n");

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empId != 0) {  // Only display valid records
            printf("%d\t%s\t%.2f\n", emp.empId, emp.empName, emp.empSalary);
        }
    }
}

void updateRecord(FILE *file) {
    struct Employee emp;
    int empId;

    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&emp, sizeof(struct Employee), 1, file) != 1 || emp.empId != empId) {
        printf("Employee not found!\n");
        return;
    }

    // Update Employee details
    printf("Enter new Employee Name: ");
    getchar(); // Consume newline character
    fgets(emp.empName, sizeof(emp.empName), stdin);
    emp.empName[strcspn(emp.empName, "\n")] = '\0';

    printf("Enter new Employee Salary: ");
    scanf("%f", &emp.empSalary);

    // Write the updated record back to the file
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Record updated successfully!\n");
}

void deleteRecord(FILE *file) {
    int empId;
    struct Employee emp;
    FILE *tempFile;

    printf("Enter Employee ID to delete: ");
    scanf("%d", &empId);

    tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        return;
    }

    rewind(file);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empId != empId) {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    // Reopen the updated file for further operations
    file = fopen("employee.dat", "rb+");

    printf("Record deleted successfully!\n");
}

int main() {
    FILE *file = fopen("employee.dat", "rb+");
    if (file == NULL) {
        file = fopen("employee.dat", "wb+");
        if (file == NULL) {
            printf("Error opening the file.\n");
            return 1;
        }
    }

    int choice;

    do {
        printf("\nEmployee Database\n");
        printf("1. Add Record\n");
        printf("2. Display All Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayAllRecords(file);
                break;
            case 3:
                updateRecord(file);
                break;
            case 4:
                deleteRecord(file);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    fclose(file);
    return 0;
}
