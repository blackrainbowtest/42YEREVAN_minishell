#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("out.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);

    execlp("ls", "ls", NULL);
    return 0;
}
