#include <stdio.h>

typedef struct {
    int id;         // Process ID
    int bt;         // Burst Time
    int priority;   // Priority (lower number = higher priority)
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];

    // Input burst time and priority for each process
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time and Priority for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }

    // Sort processes based on priority (ascending order = higher priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority > p[j].priority) {
                swap(&p[i], &p[j]);
            }
        }
    }

    // Calculate Waiting Time and Turnaround Time
    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    // Display results
    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n", p[i].id, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
