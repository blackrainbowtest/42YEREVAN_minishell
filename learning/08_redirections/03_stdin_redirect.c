#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("in.txt", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);

    execlp("wc", "wc", "-l", NULL);
    return 0;
}
