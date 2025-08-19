#include <unistd.h>
#include <stdio.h>

int main(void) {
    char *args[] = {"/usr/bin/env", NULL};
    char *new_env[] = {"MYVAR=custom_value", "PATH=/bin", NULL};

    execve("/usr/bin/env", args, new_env);
    perror("execve");
    return 1;
}
