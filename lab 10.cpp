#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "msg.txt"
void sender() {
    FILE *fp;
    char message[100];
    printf("Sender: Enter a message: ");
    fgets(message, sizeof(message), stdin);
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    fputs(message, fp)
    fclose(fp);
    printf("Sender: Message written to file.\n");
}
void receiver() {
    FILE *fp;
    char message[100];
    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Receiver: No message found. File not found.\n");
        return;
    }
    fgets(message, sizeof(message), fp);
    fclose(fp);
    printf("Receiver: Message received: %s\n", message);
}
int main() {
    int choice;
    printf("1. Sender\n");
    printf("2. Receiver\n");
    printf("Choose mode (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // consume newline left by scanf
    if (choice == 1) {
        sender();
    } else if (choice == 2) {
        receiver();
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}
