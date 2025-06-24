#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Works in Dev C++ with proper setup (MinGW)

int main() {
    FILE *fp;
    char data[] = "This is a Dev C++ compatible file I/O demo.";
    char buffer[100];

    // 1. Create and open a file for writing
    fp = fopen("myfile.txt", "w");
    if (fp == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }

    // 2. Write data to the file
    fwrite(data, sizeof(char), strlen(data), fp);
    fclose(fp); // Close after writing

    // 3. Reopen the file for reading
    fp = fopen("myfile.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file for reading.\n");
        return 1;
    }

    // 4. Move file pointer to beginning and read
    fseek(fp, 0, SEEK_SET);
    fread(buffer, sizeof(char), sizeof(buffer) - 1, fp);
    buffer[sizeof(buffer) - 1] = '\0';

    printf("File content: %s\n", buffer);
    fclose(fp);

    // 5. List current directory files (Dev C++ compatible)
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (d) {
        printf("\nFiles in current directory:\n");
        while ((dir = readdir(d)) != NULL) {
            printf("  %s\n", dir->d_name);
        }
        closedir(d);
    } else {
        printf("Unable to open current directory.\n");
    }

    return 0;
}

