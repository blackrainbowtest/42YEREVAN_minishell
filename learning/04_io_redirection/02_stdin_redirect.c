#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int fd = open("input.txt", O_RDONLY);
    dup2(fd, 0);
    close(fd);

    char buffer[100];
    int n = read(0, buffer, 100);
    write(1, buffer, n);
    return 0;
}
