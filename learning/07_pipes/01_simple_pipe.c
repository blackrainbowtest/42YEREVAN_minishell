#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    char buffer[100];

    pipe(fd);

    write(fd[1], "Hello through pipe!\n", 20);
    read(fd[0], buffer, sizeof(buffer));

    printf("Received: %s", buffer);
    return 0;
}
