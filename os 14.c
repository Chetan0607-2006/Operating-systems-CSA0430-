#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define NAME_LENGTH 30

// Structure for directory
struct Directory {
    char fileNames[MAX_FILES][NAME_LENGTH];
    int fileCount;
};

// Function declarations
void createFile(struct Directory* dir);
void deleteFile(struct Directory* dir);
void searchFile(struct Directory* dir);
void displayFiles(struct Directory* dir);

int main() {
    struct Directory dir;
    dir.fileCount = 0;

    int choice;

    while (1) {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createFile(&dir);
                break;
            case 2:
                deleteFile(&dir);
                break;
            case 3:
                searchFile(&dir);
                break;
            case 4:
                displayFiles(&dir);
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Function to create a file
void createFile(struct Directory* dir) {
	int i;
    if (dir->fileCount >= MAX_FILES) {
        printf("Directory full. Cannot create more files.\n");
        return;
    }

    char name[NAME_LENGTH];
    printf("Enter file name to create: ");
    scanf("%s", name);

    // Check for duplicate file
    for (i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->fileNames[i], name) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(dir->fileNames[dir->fileCount], name);
    dir->fileCount++;
    printf("File created successfully.\n");
}

// Function to delete a file
void deleteFile(struct Directory* dir) {
	int i;
	int j;
    char name[NAME_LENGTH];
    printf("Enter file name to delete: ");
    scanf("%s", name);
    for (i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->fileNames[i], name) == 0) {
            // Shift remaining files
            for ( j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->fileNames[j], dir->fileNames[j + 1]);
            }
            dir->fileCount--;
            printf("File deleted successfully.\n");
            return;
        }
    }

    printf("File not found.\n");
}

// Function to search a file
void searchFile(struct Directory* dir) {
	int i;
    char name[NAME_LENGTH];
    printf("Enter file name to search: ");
    scanf("%s", name);

    for ( i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->fileNames[i], name) == 0) {
            printf("File '%s' found at position %d.\n", name, i + 1);
            return;
        }
    }

    printf("File not found.\n");
}

// Function to display all files
void displayFiles(struct Directory* dir) {
	int i;
    if (dir->fileCount == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Files in directory:\n");
    for (i = 0; i < dir->fileCount; i++) {
        printf("%d. %s\n", i + 1, dir->fileNames[i]);
    }
}

