#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.dat"

struct Employee {
    int id;
    char name[30];
    float salary;
};

// Function to add employee
void addEmployee() {
    struct Employee emp;
    FILE *fp = fopen(FILE_NAME, "ab"); // append in binary mode

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    printf("Employee added successfully.\n");
}

// Function to search employee by ID
void searchEmployee() {
    struct Employee emp;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("Employee Found:\n");
            printf("ID: %d\nName: %s\nSalary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee with ID %d not found.\n", id);

    fclose(fp);
}

// Function to update salary
void updateSalary() {
    struct Employee emp;
    int id, found = 0;
    FILE *fp = fopen(FILE_NAME, "rb+"); // read and write binary

    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("Enter Employee ID to update salary: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(emp), 1, fp)) {
        if (emp.id == id) {
            printf("Current Salary: %.2f\n", emp.salary);
            printf("Enter new salary: ");
            scanf("%f", &emp.salary);

            fseek(fp, -sizeof(emp), SEEK_CUR); // move file pointer back
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Salary updated.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee with ID %d not found.\n", id);

    fclose(fp);
}

// Function to display all employees
void displayEmployees() {
    struct Employee emp;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("No employee data found.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    while (fread(&emp, sizeof(emp), 1, fp)) {
        printf("ID: %d\tName: %s\tSalary: %.2f\n", emp.id, emp.name, emp.salary);
    }

    fclose(fp);
}

int main() {
    int choice;

    do {
        printf("\n--- Employee Management System ---\n");
        printf("1. Add Employee\n");
        printf("2. Search Employee\n");
        printf("3. Update Salary\n");
        printf("4. Display All\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: searchEmployee(); break;
            case 3: updateSalary(); break;
            case 4: displayEmployees(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

