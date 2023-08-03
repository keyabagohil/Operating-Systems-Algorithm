#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 10

typedef struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int is_completed;
} process;

int main() {
    int n, time = 0, smallest, completed = 0, total_turnaround_time = 0, total_waiting_time = 0;
    process processes[MAX_PROCESS], temp;
    FILE *fp;

    fp = fopen("SJB.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i+1;
        fscanf(fp, "%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].is_completed = 0;
    }

    fclose(fp);

    // Sort processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Run SJF algorithm
    while (completed != n) {
        smallest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].is_completed == 0) {
                if (smallest == -1 || processes[i].burst_time < processes[smallest].burst_time) {
                    smallest = i;
                }
            }
        }
        // printf("Smallest %d \n",smallest);

        if (smallest == -1) {
            time++;
        } else {
            processes[smallest].completion_time = time + processes[smallest].burst_time;
            processes[smallest].turnaround_time = processes[smallest].completion_time - processes[smallest].arrival_time;
            processes[smallest].waiting_time = processes[smallest].turnaround_time - processes[smallest].burst_time;
            total_turnaround_time += processes[smallest].turnaround_time;
            total_waiting_time += processes[smallest].waiting_time;
            processes[smallest].is_completed = 1;
            completed++;
            time = processes[smallest].completion_time;
        for (int j = 0; j < processes[smallest].burst_time; j++) {
            printf("P%d ", processes[smallest].pid);
        }
        }
    }
    printf("\n");
    // Print results
    printf("Average turn-around time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average waiting time: %.2f\n", (float)total_waiting_time / n);

    // printf("Gantt Chart:\n");
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < processes[i].burst_time; j++) {
    //         printf("P%d ", processes[i].pid);
    //     }
    // }
    printf("\n");

    return 0;
}
