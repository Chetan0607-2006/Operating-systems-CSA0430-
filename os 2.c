//os lab 2
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int src = open(argv[1], O_RDONLY);
    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf[BUF_SIZE];
    ssize_t n;

    while ((n = read(src, buf, BUF_SIZE)) > 0) {
        write(dest, buf, n);
    }

    close(src);
    close(dest);
    return 0;
}

