#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    long long remaining_time;
    long long turnaround;
} Process;

typedef struct Node {
    int index;
    struct Node *next;
} Node;

void enqueue(Node **head, Node **tail, int index) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->index = index;
    new_node->next = NULL;
    if (*tail) {
        (*tail)->next = new_node;
    } else {
        *head = new_node;
    }
    *tail = new_node;
}

int dequeue(Node **head, Node **tail) {
    if (*head == NULL) return -1;
    int index = (*head)->index;
    Node *temp = *head;
    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return index;
}

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

    for (int i = 0; i < N; i++) {
        int pid, time_sec;
        scanf("%d %d", &pid, &time_sec);
        processes[i].pid = pid;
        processes[i].remaining_time = (long long)time_sec * 1000;
        processes[i].turnaround = 0;
    }

    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < N; i++) {
        enqueue(&head, &tail, i);
    }

    long long current_time = 0;

    while (head != NULL) {
        int idx = dequeue(&head, &tail);

        if (processes[idx].remaining_time <= time_slice) {
            current_time += processes[idx].remaining_time;
            processes[idx].turnaround = current_time;
            processes[idx].remaining_time = 0;
        } else {
            current_time += time_slice;
            processes[idx].remaining_time -= time_slice;
            enqueue(&head, &tail, idx);
        }
    }

    qsort(processes, N, sizeof(Process), compare);

    for (int i = 0; i < N; i++) {
        printf("%d (%lld)\n", processes[i].pid, processes[i].turnaround);
    }

    return 0;
}
