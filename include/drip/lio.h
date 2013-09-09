#ifndef DRIP_LIO_H
#define DRIP_LIO_H

#include <stdio.h>
#include <drip/lstring.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* IO Operations */

char* lgetline(FILE* file);

char* lslurp(const char* filename);
void* lslurpb(const char* filename, size_t* size_return);

void ldump(const char* filename, const char* text);
void ldumpb(const char* filename, const void* data, size_t len);

char* ltempname(const char* prefix);

#ifdef __cplusplus
}
#endif

#endif
