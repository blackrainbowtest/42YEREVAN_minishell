#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    printf("Programm is running. PID: %d\n", getpid());

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        // Daughter process
        printf("I am a child process! My PID is %d, parent PID is %d\n", getpid(), getppid());
    }
    else
    {
        // Parent process
        printf("I am the parent process! Child PID: %d, my PID: %d\n", pid, getpid());
    }

    return (0);
}