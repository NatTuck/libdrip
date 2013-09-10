
#include <stdio.h>
#include <drip/lio.h>

int
main(int argc, char* argv[])
{
    char* tmp = ltempname("bacon");
    printf("temp name: %s\n", tmp); 
    ldump(tmp, "The quick brown fox\n");
    return 0;
}
