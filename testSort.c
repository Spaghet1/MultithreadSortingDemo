#include "MergeSorts/mergesort.h"
#include "MergeSorts/mergesort.h"
#include "Utils/SortFunc.h"
#include "Utils/timing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 1024
#define MAX_SIZE 1024

extern int threadDepth;

int main(int argc, char** argv) {
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "usage: <EXEC> <SORT> <OPT: MAX THREAD DEPTH>\n");
		printFuncs();
		return 1;
	}
	void (*func)(int32_t*, size_t) = findFunc(argv[1]);
	if (func == NULL) {
		printFuncs();
		return 1;
	}
	if (argc == 3) {
		threadDepth = atoi(argv[2]);
	}
	srand(time(NULL));
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		uint32_t size = rand() % MAX_SIZE + 1;
		int32_t* array = malloc(sizeof(int32_t) * (size));
		for (unsigned int j = 0; j < size; j++) array[j] = rand();
		func(array, size);
		for (unsigned int j = 0; j < size - 1; j++) {
			if(array[j] > array[j + 1]) {
				fprintf(stderr, "test failed!\n");
				return 1;
			}
		}
		// printf("test succeeded\n");
	}
	printf("all tests succeeded\n");
	return 0;
}
