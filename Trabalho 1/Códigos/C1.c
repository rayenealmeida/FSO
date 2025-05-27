#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

int main() {
    char command_path[256];
    char argument[256];
    double total_elapsed_time = 0.0;

    while (1) {
        if (fgets(command_path, sizeof(command_path), stdin) == NULL) {
            break;
        }
        command_path[strcspn(command_path, "\n")] = 0;

        if (fgets(argument, sizeof(argument), stdin) == NULL) {
            break;
        }
        argument[strcspn(argument, "\n")] = 0;

        struct timeval start_time, end_time;
        pid_t pid;
        int status;
        double elapsed_time;

        gettimeofday(&start_time, NULL);
        pid = fork();

        if (pid == -1) {
            perror("fork");
            continue;
        } else if (pid == 0) {
            execl(command_path, command_path, argument, NULL);
            _exit(errno);
        } else {
            wait(&status);
            gettimeofday(&end_time, NULL);

            elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                           (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

            if (WIFEXITED(status)) {
                int return_code = WEXITSTATUS(status);
                printf("> Demorou %.1f segundos, retornou %d\n", elapsed_time, return_code);
                total_elapsed_time += elapsed_time;
            } else if (WIFSIGNALED(status)) {
                printf("> Demorou %.1f segundos, retornou %d\n", elapsed_time, WTERMSIG(status) + 128);
            } else {
                printf("> Demorou %.1f segundos, retornou %d\n", elapsed_time, -1); 
                total_elapsed_time += elapsed_time;
            }
        }
    }

    printf(">> O tempo total foi de %.1f segundos\n", total_elapsed_time);

    return 0;
}