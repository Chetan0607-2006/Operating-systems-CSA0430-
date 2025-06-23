//os code 1
#include <windows.h>
#include <stdio.h>
int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize memory
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command line: run child.exe
    char command[] = "child.exe"; // Make sure child.exe is in the same folder

    // Create the child process
    if (!CreateProcess(
        NULL,       // No module name (use command line)
        command,    // Command line to execute
        NULL,       // Process handle not inheritable
        NULL,       // Thread handle not inheritable
        FALSE,      // Set handle inheritance to FALSE
        0,          // No creation flags
        NULL,       // Use parent's environment block
        NULL,       // Use parent's current directory
        &si,        // Pointer to STARTUPINFO structure
        &pi)        // Pointer to PROCESS_INFORMATION structure
    ) {
        printf("Failed to create child process. Error: %lu\n", GetLastError());
        return 1;
    }

    printf("Parent Process:\n");
    printf("  Parent PID: %lu\n", GetCurrentProcessId());
    printf("  Child PID: %lu\n", pi.dwProcessId);

    // Wait for child process to finish
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

