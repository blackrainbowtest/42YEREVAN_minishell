#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    write(1, "SIGINT caught!\n", 15);
}

int main(void) {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);

    printf("PID = %d, press Ctrl+C\n", getpid());
    while (1)
        pause();
    return 0;
}
