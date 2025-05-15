#include <stdio.h>

#define MAX 10

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) { // Each process
        for (int j = 0; j < m; j++) { // Each block
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
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
    for (int i = 0; i < n; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
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
    for (int i = 0; i < n; i++) {
        printf("Process %d of size %d -> ", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("Block %d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX], processSize[MAX], m, n;
    int blockCopy1[MAX], blockCopy2[MAX], blockCopy3[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of memory blocks: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
        blockCopy1[i] = blockSize[i]; // For First Fit
        blockCopy2[i] = blockSize[i]; // For Best Fit
        blockCopy3[i] = blockSize[i]; // For Worst Fit
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockCopy1, m, processSize, n);
    bestFit(blockCopy2, m, processSize, n);
    worstFit(blockCopy3, m, processSize, n);

    return 0;
}
