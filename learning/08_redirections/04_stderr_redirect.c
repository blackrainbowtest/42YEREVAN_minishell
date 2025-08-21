#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("err.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, STDERR_FILENO);
    close(fd);

    execlp("ls", "ls", "/no/such/dir", NULL);
    return 0;
}
