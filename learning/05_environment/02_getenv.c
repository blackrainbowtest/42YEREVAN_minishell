#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *path = getenv("PATH");
    if (path)
        printf("PATH = %s\n", path);
    else
        printf("PATH not found\n");
    return 0;
}
