#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>

double get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main() {
    char path[256];
    char arg[256];
    double total_time = 0.0;
    
    while (scanf("%255s %255s", path, arg) == 2) {
        double start_time = get_current_time();
        pid_t pid = fork();
        
        if (pid == 0) { // Processo filho
            // Executa o comando
            execl(path, path, arg, NULL);
            
            // Se execl retornar, houve erro
            printf("> Erro: %s\n", strerror(errno));
            exit(2);
        } else if (pid > 0) { // Processo pai
            int status;
            waitpid(pid, &status, 0);
            double end_time = get_current_time();
            double elapsed = end_time - start_time;
            
            if (WIFEXITED(status)) {
                printf("> Demorou %.1f segundos, retornou %d\n", elapsed, WEXITSTATUS(status));
                total_time += elapsed;
            }
        } else { // Erro no fork
            perror("fork");
            exit(1);
        }
    }
    
    printf(">> O tempo total foi de %.1f segundos\n", total_time);
    return 0;
}