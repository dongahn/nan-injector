#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <math.h>

#if USE_QUIET_NAN
# define NAN_BIT_PATTERN 0x7FF8000000000000
#else
# define NAN_BIT_PATTERN 0x7FF7FFFFFFFFFFFF
#endif

void *malloc (size_t size)
{
    static void *(*mallocp) (size_t size);
    char *error;
    void *ptr;

    /* get address of libc malloc */
    if (!mallocp) {
        mallocp = dlsym (RTLD_NEXT, "malloc");
        if ((error = dlerror ()) != NULL) {
            fprintf (stderr, "%s", error);
            exit(1);
        }
    }

    ptr = mallocp(size);

    // only inject NANs if the size is a multiple of 8B
    if (!(size & 7)) {
        int i = 0;
        long *trav = (long *) ptr;
        for (i = 0; i < size/8; i++)
            trav[i] = NAN_BIT_PATTERN;
    }

    return ptr;
}

/*
 * vi: ts=4 sw=4 expandtab
 */
