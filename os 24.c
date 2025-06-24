#include <stdio.h>
#include <fcntl.h>     // open(), O_CREAT, etc.
#include <unistd.h>    // read(), write(), lseek(), close()
#include <string.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytesRead, bytesWritten;

    // Open (or create) a file
    fd = open("example.txt", O_CREAT | O_RDWR, 0644);  // rw-r--r--
    if (fd < 0) {
        perror("File open failed");
        return 1;
    }
    printf("File opened successfully with fd: %d\n", fd);

    // Write to file
    char data[] = "This is a demo of UNIX system calls.\n";
    bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten < 0) {
        perror("Write failed");
        close(fd);
        return 1;
    }
    printf("Wrote %ld bytes to the file.\n", bytesWritten);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read back from file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Read failed");
        close(fd);
        return 1;
    }

    buffer[bytesRead] = '\0';  // Null-terminate
    printf("Read %ld bytes: %s", bytesRead, buffer);

    // Close the file
    close(fd);
    printf("File closed.\n");

    return 0;
}

