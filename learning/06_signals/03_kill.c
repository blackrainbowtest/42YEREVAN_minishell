#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child running (pid=%d)\n", getpid());
        while (1)
            sleep(1);
    } else {
        sleep(3);
        printf("Killing child...\n");
        kill(pid, SIGTERM);
    }
    return 0;
}
