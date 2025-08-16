#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char *msg = malloc(20);
    strcpy(msg, "Hello");

    pid_t pid = fork();

    if (pid == 0)
    {
        strcpy(msg, "Child");
        printf("[Child] msg=%s, ptr=%p\n", msg, (void*)msg);
    }
    else
    {
        sleep(1); // wait for the child to change the string
        printf("[Parent] msg=%s, ptr=%p\n", msg, (void*)msg);
    }

    free(msg);
    return 0;
}