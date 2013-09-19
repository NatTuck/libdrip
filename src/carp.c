
#include <stdio.h>
#include <stdlib.h>

#include "drip/carp.h"

void 
drip_carp_real(const char* filename, const int line, const char* message)
{
    fprintf(stderr, "Fatal error at %s:%d\n\t%s\n", filename, line, message);
    fflush(stderr);
    abort();
}
