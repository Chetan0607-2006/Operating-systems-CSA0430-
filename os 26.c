#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create and write to a file
void createFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }
    char data[100];
    printf("Enter data to write: ");
    fflush(stdin);
    fgets(data, sizeof(data), stdin);
    fputs(data, fp);
    fclose(fp);
    printf("File created and data written successfully.\n");
}

// Function to read a file
void readFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }
    char ch;
    printf("\nFile content:\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
    printf("\n");
}

// Function to append data to a file
void appendFile(const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("File not found.\n");
        return;
    }
    char data[100];
    printf("Enter data to append: ");
    fflush(stdin);
    fgets(data, sizeof(data), stdin);
    fputs(data, fp);
    fclose(fp);
    printf("Data appended successfully.\n");
}

// Function to delete a file
void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file or file not found.\n");
    }
}

int main() {
    int choice;
    char filename[100];

    do {
        printf("\n--- File Management System ---\n");
        printf("1. Create & Write File\n");
        printf("2. Read File\n");
        printf("3. Append to File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        fflush(stdin); // Clear input buffer

        if (choice >= 1 && choice <= 4) {
            printf("Enter file name: ");
            gets(filename);
        }

        switch (choice) {
            case 1:
                createFile(filename);
                break;
            case 2:
                readFile(filename);
                break;
            case 3:
                appendFile(filename);
                break;
            case 4:
                deleteFile(filename);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}

