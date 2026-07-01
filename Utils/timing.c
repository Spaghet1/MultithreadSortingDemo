#include <time.h>
#include <stdio.h>
#include "timing.h"

struct timespec timeDiff(struct timespec start, struct timespec end) {
	long nsecDiff = end.tv_nsec - start.tv_nsec;
	long secDiff = end.tv_sec - start.tv_sec;
	if (nsecDiff < 0) {
		--secDiff;
		nsecDiff += 1e9;
	}
	struct timespec diffStruct = {
		.tv_sec = secDiff,
		.tv_nsec = nsecDiff
	};
	return diffStruct;
}

double timespecToDouble(struct timespec time) {
	return time.tv_sec + time.tv_nsec * 1e-9;
}
