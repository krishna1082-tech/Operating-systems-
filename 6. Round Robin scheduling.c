#include <stdio.h>

int main() {
    int n, i, timeQuantum;
    int bt[100], rt[100], wt[100] = {0}, tat[100]; // bt = burst time, rt = remaining time
    int time = 0, done;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // Initially, remaining time is same as burst time
    }

    // Input Time Quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Round Robin scheduling
    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                if (rt[i] > timeQuantum) {
                    time += timeQuantum;
                    rt[i] -= timeQuantum;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i]; // Final waiting time
                    rt[i] = 0;
                }
            }
        }
    } while (!done);

    // Calculate Turnaround Time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Output
    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
