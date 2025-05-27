#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    long long remaining_time;
    long long turnaround;
} Process;

typedef struct {
    int index;
} QueueItem;

int compare(const void *a, const void *b) {
    const Process *p1 = (const Process *)a;
    const Process *p2 = (const Process *)b;
    if (p1->turnaround < p2->turnaround) return -1;
    if (p1->turnaround > p2->turnaround) return 1;
    return 0;
}

int main() {
    int N, time_slice;
    scanf("%d %d", &N, &time_slice);

    Process processes[N];
    QueueItem queue[N * 100]; // fila bem maior que N, suficiente para qualquer caso
    int front = 0, rear = 0;

    for (int i = 0; i < N; i++) {
        int pid, time_sec;
        scanf("%d %d", &pid, &time_sec);
        processes[i].pid = pid;
        processes[i].remaining_time = (long long)time_sec * 1000;
        processes[i].turnaround = 0;
        queue[rear++] = (QueueItem){i};
    }

    long long current_time = 0;

    while (front < rear) {
        int idx = queue[front++].index;
        if (processes[idx].remaining_time <= time_slice) {
            current_time += processes[idx].remaining_time;
            processes[idx].turnaround = current_time;
            processes[idx].remaining_time = 0;
        } else {
            current_time += time_slice;
            processes[idx].remaining_time -= time_slice;
            queue[rear++] = (QueueItem){idx};
        }
    }

    qsort(processes, N, sizeof(Process), compare);

    for (int i = 0; i < N; i++) {
        printf("%d (%lld)\n", processes[i].pid, processes[i].turnaround);
    }

    return 0;
}
