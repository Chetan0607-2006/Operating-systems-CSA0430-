#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void grep(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    int lineNum = 0, found = 0;

    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        lineNum++;
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", lineNum, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Pattern '%s' not found in file '%s'\n", pattern, filename);
    }

    fclose(file);
}

int main() {
    char filename[100], pattern[100];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline

    printf("Enter search pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove newline

    grep(filename, pattern);

    return 0;
}

