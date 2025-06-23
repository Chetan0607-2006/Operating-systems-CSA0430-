#include <stdio.h>

int main() {
    int n, tq, time = 0, done;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];
    int i;
    for (i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        wt[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                int exec = rt[i] < tq ? rt[i] : tq;
                time += exec;
                rt[i] -= exec;
                if (rt[i] == 0)
                    wt[i] = time - bt[i];
            }
        }
    } while (!done);

    float total_wt = 0, total_tat = 0;
    printf("\nP\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAvg WT = %.2f\n", total_wt / n);
    printf("Avg TAT = %.2f\n", total_tat / n);

    return 0;
}

