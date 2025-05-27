#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int remaining_time; 
    int turnaround;
} Process;

typedef struct {
    int pid;
    int turnaround;
} CompletedProcess;

int compare(const void *a, const void *b) {
    CompletedProcess *p1 = (CompletedProcess *)a;
    CompletedProcess *p2 = (CompletedProcess *)b;
    return p1->turnaround - p2->turnaround;
}

int main() {
    int N, time_slice;
    scanf("%d", &N);
    scanf("%d", &time_slice);
    
    Process *processes = malloc(N * sizeof(Process));
    for (int i = 0; i < N; i++) {
        int pid, time_seconds;
        scanf("%d %d", &pid, &time_seconds);
        processes[i].pid = pid;
        processes[i].remaining_time = time_seconds * 1000; 
        processes[i].turnaround = 0;
    }
    
    int current_time = 0;
    int completed = 0;
    int *finished = calloc(N, sizeof(int));
    CompletedProcess *completed_processes = malloc(N * sizeof(CompletedProcess));
    
    while (completed < N) {
        for (int i = 0; i < N; i++) {
            if (finished[i]) continue;
            
            if (processes[i].remaining_time > time_slice) {
                processes[i].remaining_time -= time_slice;
                current_time += time_slice;
            } else {
                current_time += processes[i].remaining_time;
                completed_processes[completed].pid = processes[i].pid;
                completed_processes[completed].turnaround = current_time;
                processes[i].remaining_time = 0;
                finished[i] = 1;
                completed++;
            }
        }
    }
    
    qsort(completed_processes, N, sizeof(CompletedProcess), compare);
    
    for (int i = 0; i < N; i++) {
        printf("%d (%d)\n", completed_processes[i].pid, completed_processes[i].turnaround);
    }
    
    free(processes);
    free(finished);
    free(completed_processes);
    return 0;
}