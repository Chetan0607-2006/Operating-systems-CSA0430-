#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int arrival[n], burst[n], priority[n], waiting[n], turnaround[n], completed[n];
    int time = 0, completedCount = 0;
    float totalWaiting = 0, totalTurnaround = 0;

    for (i = 0; i < n; i++) {
        printf("Process %d Arrival time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("Process %d Burst time: ", i + 1);
        scanf("%d", &burst[i]);
        printf("Process %d Priority (lower number = higher priority): ", i + 1);
        scanf("%d", &priority[i]);
        completed[i] = 0;
    }

    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 1e9; // Large number for min comparison
        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && !completed[i] && priority[i] < highestPriority) {
                highestPriority = priority[i];
                idx = i;
            }
        }

        if (idx != -1) {
            waiting[idx] = time - arrival[idx];
            time += burst[idx];
            turnaround[idx] = time - arrival[idx];
            completed[idx] = 1;
            completedCount++;
        } else {
            time++;
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival[i], burst[i], priority[i], waiting[i], turnaround[i]);
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaround / n);

    return 0;
}

