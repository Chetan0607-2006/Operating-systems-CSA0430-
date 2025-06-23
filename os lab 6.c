#include <stdio.h>
#include <limits.h>

int main() {
    int n,i, time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int arrival[n], burst[n], priority[n], remaining[n];
    int waiting[n], turnaround[n], done[n];

    for ( i = 0; i < n; i++) {
        printf("Process %d Arrival time, Burst time, Priority: ", i + 1);
        scanf("%d %d %d", &arrival[i], &burst[i], &priority[i]);
        remaining[i] = burst[i];
        done[i] = 0;
        waiting[i] = 0;
        turnaround[i] = 0;
    }

    int currentProcess = -1;

    while (completed < n) {
        int highestPriority = INT_MAX;
        int idx = -1;

        // Find process with highest priority that has arrived and not completed
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && !done[i] && priority[i] < highestPriority && remaining[i] > 0) {
                highestPriority = priority[i];
                idx = i; 
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            done[idx] = 1;
            completed++;
            turnaround[idx] = time - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];
        }
    }

    printf("\nP#\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival[i], burst[i], priority[i], waiting[i], turnaround[i]);
    }

    return 0;
}

