#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Sort processes by burst time
void sortByBurstTime(struct Process p[], int n) {
    struct Process temp;
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

// Calculate waiting and turnaround times
void calculateTimes(struct Process p[], int n) {
    int i;
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;

    for (i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

// Display results
void display(struct Process p[], int n) {
    int i;
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process* p = (struct Process*)malloc(n * sizeof(struct Process));

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    sortByBurstTime(p, n);
    calculateTimes(p, n);
    display(p, n);

    free(p);
    return 0;
}

