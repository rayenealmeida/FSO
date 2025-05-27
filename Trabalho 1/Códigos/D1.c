#include <pthread.h>

int count = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct thread_arg {
    int vezes;
};

int work(int id);

void *thread_func(void *arg) {
    struct thread_arg *args = (struct thread_arg *)arg;
    
    for (int i = 0; i < args->vezes; ) {
        int current_id;
        
        pthread_mutex_lock(&mut);
        current_id = count;
        count++;
        pthread_mutex_unlock(&mut);
        
        work(current_id);
        i++;
    }
    
    return NULL;
}

void do_all_work(int n) {
    for (int i = 0; i < n; i++) {
        work(i);
    }
    return;
}