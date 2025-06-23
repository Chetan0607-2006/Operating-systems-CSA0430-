#include <windows.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 1024
TCHAR szName[] = TEXT("Global\\MySharedMemory");

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    
        NULL,                    
        PAGE_READWRITE,          
        0,                       
        BUF_SIZE,                
        szName);             

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map a view of the file into the address space
    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,            
	    FILE_MAP_ALL_ACCESS, 
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Simulate writing
    char message[BUF_SIZE];
    printf("Enter message to write to shared memory: ");
    fgets(message, BUF_SIZE, stdin);
    CopyMemory((PVOID)pBuf, message, strlen(message) + 1);

    // Simulate reading
    printf("Reading from shared memory...\n");
    printf("Message: %s\n", pBuf);

    // Clean up
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

