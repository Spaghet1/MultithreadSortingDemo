#include "MergeSorts/mergesort.h"
#include "Utils/SortFunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern int threadDepth;

int main(int argc, char** argv) {
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "usage: <EXEC> <SORT> <SIZE> <OPT: MAX THREAD DEPTH>\n");
		printFuncs();
		return 1;
	}
	void (*func)(int32_t*, size_t) = findFunc(argv[1]);
	if (!func) {
		printFuncs();
		return 1;
	}
	size_t size = strtoull(argv[2], NULL, 0);
	if (size == 0) {
		fprintf(stderr, "size should be > 0\n");
		return 1;
	}
	if (argc == 4) threadDepth = atoi(argv[3]);
	srand(time(NULL));
	int32_t* array = malloc(sizeof(int32_t) * (size));
	for (unsigned int j = 0; j < size; j++) array[j] = rand();
	func(array, size);
	return 0;
}
