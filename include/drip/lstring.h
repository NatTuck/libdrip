#ifndef DRIP_LSTRING_H
#define DRIP_LSTRING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

/* Boring string utility functions */

int streq(const char* aa, const char* bb);

/* String operations that assume gc for results. */

char* lstrdupn(const char* ss, int nn);
char* lstrdup(const char* ss);
char* lstrcat(const char* aa, const char* bb);
char* lsprintf(const char* fmt, ...);
char* lsubstr(const char* ss, int offset, int length);
char* lchomp(const char* ss);
char* lstripc(const char cc, const char* ss);

/* Leaky void* ops */

void* lmemcpy(const void* src, size_t n);

/* Vector of strings. */

typedef struct lstrvec {
    int size;
    char** xs;
} lstrvec;

lstrvec* lstrvec_alloc(int size);
int lstrvec_size(lstrvec* vec); 
char* lstrvec_get(lstrvec* vec, int ii);
void lstrvec_set(lstrvec* vec, int ii, char* vv);
int lstrvec_contains(lstrvec* vec, const char* ss);

/* String / Vector Ops */

lstrvec* lwords(const char* ss);
lstrvec* lsplitc(const char cc, const char* ss);

#ifdef __cplusplus
}
#endif

#endif
