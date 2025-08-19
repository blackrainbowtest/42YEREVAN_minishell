#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);
    close(fd);
    write(1, "Hello file\n", 11);
    return 0;
}
