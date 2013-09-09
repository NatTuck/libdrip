
#include <stdio.h>
#include <drip/lio.h>

int
main(int argc, char* argv[])
{
    printf("temp name: %s\n", ltempname("bacon"));
    return 0;
}
