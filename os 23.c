#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int blocks,int i,int j, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];

    // Initially no process is allocated
    for ( i = 0; i < processes; i++) {
        allocation[i] = -1;
    }

    // Try to allocate each process
    for (i = 0; i < processes; i++) {
        for ( j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break; // move to next process
            }
        }
    }

    // Display allocation results
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for ( i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
	int i;
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter sizes of %d memory blocks:\n", blocks);
    for ( i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes:\n", processes);
    for ( i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    return 0;
}
