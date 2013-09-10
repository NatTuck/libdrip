
#include <stdio.h>
#include <drip/lio.h>

int
main(int argc, char* argv[])
{
    char* text = lshell("echo the quick brown fox");
    printf("text: %s\n", text);
    return 0;
}
