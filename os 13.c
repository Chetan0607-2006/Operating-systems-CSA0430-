#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// Function for First Fit allocation
void firstFit(int blockSize[], int i,int j,int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (i = 0; i < processes; i++) {
        allocation[i] = -1;
        for (j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Function for Best Fit allocation
void bestFit(int blockSize[],int i,int j, int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for ( i = 0; i < processes; i++) {
        int bestIdx = -1;
        allocation[i] = -1;
        for (j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
void worstFit(int blockSize[],int i,int j, int blocks, int processSize[], int processes) {
    int allocation[MAX_PROCESSES];
    for (i = 0; i < processes; i++) {
        int worstIdx = -1;
        allocation[i] = -1;
        for (j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < processes; i++) {
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
    for (i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &processes);
    printf("Enter sizes of %d processes:\n", processes);
    for (i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Create copies of block sizes for each strategy
    int blockSize1[MAX_BLOCKS], blockSize2[MAX_BLOCKS], blockSize3[MAX_BLOCKS];
    for (i = 0; i < blocks; i++) {
        blockSize1[i] = blockSize[i];
        blockSize2[i] = blockSize[i];
        blockSize3[i] = blockSize[i];
    }
    return 0;
}

