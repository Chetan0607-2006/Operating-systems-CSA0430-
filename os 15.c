#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_FILES 10
#define NAME_LEN 30

// Structure to store files under a user
struct Directory {
    char userName[NAME_LEN];
    char fileNames[MAX_FILES][NAME_LEN];
    int fileCount;
};

int userCount = 0;
struct Directory users[MAX_USERS];

// Function to create a user directory
void createUser() {
	int i;
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    char uname[NAME_LEN];
    printf("Enter user name: ");
    scanf("%s", uname);

    // Check for duplicate user
    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].userName, uname) == 0) {
            printf("User already exists.\n");
            return;
        }
    }

    strcpy(users[userCount].userName, uname);
    users[userCount].fileCount = 0;
    userCount++;

    printf("User directory created successfully.\n");
}

// Function to create a file under a user
void createFile() {
	int i;
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter user name: ");
    scanf("%s", uname);

    // Find user
    int found = -1;
    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].userName, uname) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("User not found.\n");
        return;
    }

    if (users[found].fileCount >= MAX_FILES) {
        printf("File limit reached for this user.\n");
        return;
    }

    printf("Enter file name to create: ");
    scanf("%s", fname);

    // Check if file already exists
    for (i = 0; i < users[found].fileCount; i++) {
        if (strcmp(users[found].fileNames[i], fname) == 0) {
            printf("File already exists.\n");
            return;
        }
    }

    strcpy(users[found].fileNames[users[found].fileCount], fname);
    users[found].fileCount++;

    printf("File created successfully.\n");
}

// Function to delete a file
void deleteFile() {
	int i;
	int j;
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter user name: ");
    scanf("%s", uname);
    printf("Enter file name to delete: ");
    scanf("%s", fname);

    int found = -1;
    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].userName, uname) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("User not found.\n");
        return;
    }

    for (i = 0; i < users[found].fileCount; i++) {
        if (strcmp(users[found].fileNames[i], fname) == 0) {
            // Shift remaining files
            for ( j = i; j < users[found].fileCount - 1; j++) {
                strcpy(users[found].fileNames[j], users[found].fileNames[j + 1]);
            }
            users[found].fileCount--;
            printf("File deleted successfully.\n");
            return;
        }
    }

    printf("File not found under user.\n");
}

// Function to search for a file
void searchFile() {
	int i;
	int j;
    char uname[NAME_LEN], fname[NAME_LEN];
    printf("Enter user name: ");
    scanf("%s", uname);
    printf("Enter file name to search: ");
    scanf("%s", fname);

    for ( i = 0; i < userCount; i++) {
        if (strcmp(users[i].userName, uname) == 0) {
            for ( j = 0; j < users[i].fileCount; j++) {
                if (strcmp(users[i].fileNames[j], fname) == 0) {
                    printf("File found under user %s.\n", uname);
                    return;
                }
            }
            printf("File not found under user %s.\n", uname);
            return;
        }
    }

    printf("User not found.\n");
}

// Function to display all users and their files
void displayAll() {
	int i;
	int j;
    if (userCount == 0) {
        printf("No users present.\n");
        return;
    }

    for ( i = 0; i < userCount; i++) {
        printf("User: %s\n", users[i].userName);
        if (users[i].fileCount == 0) {
            printf("  No files.\n");
        } else {
            for ( j = 0; j < users[i].fileCount; j++) {
                printf("  File %d: %s\n", j + 1, users[i].fileNames[j]);
            }
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Two Level Directory System ---\n");
        printf("1. Create User\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display All\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createUser(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: displayAll(); break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }

    return 0;
}

