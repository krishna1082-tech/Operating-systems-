#include <stdio.h>
#include <limits.h>

struct Process {
    int id, at, bt, rt, prio;
    int wt, tat, completed;
};

int main() {
    int n, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter Arrival Time, Burst Time and Priority (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].prio);
        p[i].rt = p[i].bt;
        p[i].completed = 0;
    }

    printf("\nGantt Chart:\n");

    int last_process = -1;
    printf("%d", time); // Start time

    while (completed < n) {
        int idx = -1, highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].prio < highest_priority) {
                highest_priority = p[i].prio;
                idx = i;
            }
        }

        if (idx != -1) {
            if (last_process != idx) {
                printf(" -> P%d", p[idx].id); // Only print when process changes
                last_process = idx;
            }
            p[idx].rt--;
            time++;

            if (p[idx].rt == 0) {
                p[idx].completed = 1;
                completed++;
                p[idx].tat = time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
            }
        } else {
            if (last_process != -2) {
                printf(" -> Idle");
                last_process = -2;
            }
            time++;
        }
    }
    printf(" -> %d\n", time); // End time

    // Table Output
    printf("\nProcess | Arrival | Burst | Priority | Waiting | Turnaround\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d      |   %d     |   %d   |    %d     |   %d     |    %d\n",
               p[i].id, p[i].at, p[i].bt, p[i].prio, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
