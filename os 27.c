#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Function to simulate ls command
void listDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("Listing files in directory: %s\n\n", path);
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    char path[100];

    printf("Enter directory path (or leave blank for current directory): ");
    fgets(path, sizeof(path), stdin);

    // Remove newline character
    path[strcspn(path, "\n")] = 0;

    // Default to current directory if input is empty
    if (strlen(path) == 0) {
        strcpy(path, ".");
    }

    listDirectory(path);

    return 0;
}

