#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t signal_count = 0;
pid_t child_pid = 0;

void signal_handler(int sig) {
    signal_count++;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    pause();

    child_pid = fork();
    if (child_pid == 0) {
        exit(0);
    } else if (child_pid > 0) {
        
        pause();
        
        // Elimina o zumbi
        waitpid(child_pid, NULL, 0);
        
        pause();
    }

    return 0;
}