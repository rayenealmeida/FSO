#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    long remaining_time_ms;
} Process;

typedef struct {
    Process *data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->size = 0;
    q->rear = capacity - 1;
    q->data = (Process*) malloc(capacity * sizeof(Process));
    return q;
}

int isEmpty(Queue *q) {
    return (q->size == 0);
}

void enqueue(Queue *q, Process item) {
    if (q->size == q->capacity) return; 
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = item;
    q->size++;
}

Process dequeue(Queue *q) {
    Process item = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

int main() {
    int n;
    long quantum_ms;

    scanf("%d", &n);
    scanf("%ld", &quantum_ms);

    Queue *q = createQueue(n);

    for (int i = 0; i < n; i++) {
        int pid;
        long t;
        scanf("%d %ld", &pid, &t);
        Process p;
        p.pid = pid;
        p.remaining_time_ms = t * 1000;
        enqueue(q, p);
    }

    long current_time = 0;
    Process finished_order[n];
    int finish_count = 0;

    while (!isEmpty(q)) {
        Process p = dequeue(q);
        if (p.remaining_time_ms <= quantum_ms) {
            current_time += p.remaining_time_ms;
            p.remaining_time_ms = 0;
            finished_order[finish_count++] = p;
            finished_order[finish_count - 1].remaining_time_ms = current_time; 
        } else {
            current_time += quantum_ms;
            p.remaining_time_ms -= quantum_ms;
            enqueue(q, p);
        }
    }

    for (int i = 0; i < finish_count; i++) {
        printf("%d (%ld)\n", finished_order[i].pid, finished_order[i].remaining_time_ms);
    }

    free(q->data);
    free(q);

    return 0;
}
