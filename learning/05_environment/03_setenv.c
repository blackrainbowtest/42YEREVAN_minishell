#include <stdio.h>
#include <stdlib.h>

int main(void) {
    setenv("MYVAR", "hello_world", 1);
    printf("MYVAR = %s\n", getenv("MYVAR"));
    unsetenv("MYVAR");
    printf("MYVAR after unset = %s\n", getenv("MYVAR"));
    return 0;
}