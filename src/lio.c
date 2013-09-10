

#include <bsd/string.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <gc.h>

#include "drip/lio.h"

/* FILE* using I/O ops */

char*
lgetline(FILE* file)
{
    char*  temp = 0;
    size_t zero = 0;

    if (getline(&temp, &zero, file) == -1) {
        if (feof(file)) {
            return 0;
        }
        else {
            perror("getline in lgetline");
            fflush(stderr);
            abort();
        }
    }

    char* line = lstrdup(temp);
    free(temp);
    return line;
}

/* I/O ops that take filenames */

char*
lslurp(const char* filename)
{
    size_t ignored;
    return (char*) lslurpb(filename, &ignored);
}

void*
lslurpb(const char* filename, size_t* size_return)
{
    const size_t BS = 1024;
    void* block = alloca(BS);
    void* data  = GC_malloc_atomic(1);

    size_t count = 0;
    size_t size  = 0;

    FILE* file = fopen(filename, "r");

    while ((count = fread(block, 1, BS, file))) {
        data = GC_realloc(data, size + count);
        memcpy(data + size, block, count);
        size += count;
    }

    if (!feof(file)) {
        perror("Read error in lslurpb");
        fflush(stderr);
        abort();
    }

    fclose(file);

    *size_return = size;
    return data;
}


void 
ldump(const char* filename, const char* text)
{
    ldumpb(filename, (void*) text, strlen(text));
}


void 
ldumpb(const char* filename, const void* data, size_t len)
{
    FILE* out = fopen(filename, "wx");

    if (out == 0) {
        perror("Could not open file for ldumpb");
        fflush(stderr);
        abort();
    }

    size_t count = fwrite(data, len, 1, out);
    if (count != 1) {
        fprintf(stderr, "Error dumping data to file '%s':\n", filename);
        perror("Ack");
        fflush(stderr);
        abort();
    }
    fclose(out);
}

static
int
exists(const char* filename)
{
    struct stat info;

    int rv = lstat(filename, &info);

    if (rv == -1 && errno == ENOENT)
        return 0;
    else
        return 1;
}

char*
ltempname(const char* prefix)
{
    struct stat info;
    char* name;
    long nn = (long) getpid();

    do {
        nn = (nn * 17 + 5) % 0x10000;
        name = lsprintf("/tmp/%s-%04lx", prefix, nn);
    } while(exists(name));

    return name;
}

/* System Ops */

char*
lshell(const char* cmd)
{
    char* filename = ltempname("lshell");
    char* full_cmd = lsprintf("(%s) > %s", cmd, filename);

    int rv = system(full_cmd);
    
    if (WEXITSTATUS(rv) != 0) {
        fprintf(stderr, "lshell(%s) exited with status %d", cmd, WEXITSTATUS(rv));
        fflush(stderr);
        abort();
    }

    char* output = lslurp(filename);
    unlink(filename);
    return output;
}
