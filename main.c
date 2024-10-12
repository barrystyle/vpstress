#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lz4.h"

unsigned char *y, *z;

long long current_timestamp()
{
    long long milliseconds;
    struct timespec te;
    clock_gettime(CLOCK_REALTIME, &te);
    milliseconds = 1000LL * te.tv_sec + round(te.tv_nsec / 1e6);
    return milliseconds;
}

void compress_garbage(int mult)
{
    int c;

    // create garbage
    c = 0;
    while (c < 1048576 * mult) {
        z[c] = rand() % 256;
        ++c;
    }

    // compress
    int outsz;
    LZ4_compress_default(z, y, 1048576 * mult, outsz);
}

int main()
{
    long long st1, st2;
    int mult;

    mult = 128;

    // make space for garbage
    z = (unsigned char*)malloc(1048576 * mult);
    if (!z) {
        printf("some error (z)\n");
        free(z);
        return 0;
    }

    // make space for dest
    y = (unsigned char*)malloc(1048576 * mult);
    if (!y) {
        printf("some error (y)\n");
        free(y);
        return 0;
    }

    // do the things
    while (1) {
        st1 = current_timestamp();
        compress_garbage(mult);
        st2 = current_timestamp();
        printf("%d ms\n", st2 - st1);
    }

    // neckbeard activate
    free(z);
    free(y);

    return 1;
}
