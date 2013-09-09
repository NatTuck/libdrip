
#include <stdio.h>
#include <drip/lstring.h>

int
main(int argc, char* argv[])
{
    char *who;
    int ii;

    for (ii = 0; ii < 1024 * 1024; ++ii) {
        who = lstrdup("World");
    }

    printf("Hello, %s\n", who);
    return 0;
}
