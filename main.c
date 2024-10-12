#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "lz4.h"

long long current_timestamp()
{
	long long milliseconds;
	struct timespec te;
	clock_gettime(CLOCK_REALTIME, &te);
	milliseconds = 1000LL*te.tv_sec + round(te.tv_nsec/1e6);
	return milliseconds;
}

void compress_garbage(int mult)
{
	int c;
	unsigned char *y, *z;

	// make space for garbage
	z = (unsigned char*) malloc (1048576*mult);
	if (!z) {
            printf("some error (z)\n");
	    free(z);
            return;
	}

	// create garbage
        c = 0;
	while (c < 1048576*mult) {
	    z[c] = rand() % 256;
	    ++c;
	}

	// make space for dest
	y = (unsigned char*) malloc (1048576*mult);
	if (!y) {
	    printf("some error (y)\n");
            free(y);
            return;
	}

	// compress
	int outsz;
	LZ4_compress_default(z, y, 1048576*mult, outsz);

	// clean up
	free(z);
	free(y);
}

int main()
{
	long long st1, st2;

	while (1) {
		st1 = current_timestamp();
		compress_garbage(128);
		st2 = current_timestamp();
		printf("%d ms\n", st2-st1);
	}

	return 1;
}
