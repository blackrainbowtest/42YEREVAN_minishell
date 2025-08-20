#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main(void) {
    signal(SIGINT, handler);
    printf("Try pressing Ctrl+C (PID = %d)\n", getpid());
    while (1) {
        pause();
    }
    return 0;
}
