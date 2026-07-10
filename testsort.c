#include "MergeSorts/mergesort.h"
#include "MergeSorts/mergesort.h"
#include "Utils/SortFunc.h"
#include "Utils/timing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 100
#define MAX_SIZE 20

int comparatorTest(const void* a, const void* b) {
	return (*(int32_t*)a - *(int32_t*)b);
}

int threadDepth;

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
		int32_t* copyArray = malloc(sizeof(int32_t) * (size));
		if (!array || !copyArray) {
			fprintf(stderr, "malloc failed");
			return 1;
		}
		for (unsigned int j = 0; j < size; j++) {
			array[j] = rand();
			copyArray[j] = array[j];
		}
		func(array, size);
		qsort(copyArray, size, sizeof(int32_t), comparatorTest); // trusted sort
		for (size_t j = 0; j < size; j++) {
			if(array[j] != copyArray[j]) {
				fprintf(stderr, "test failed!\n");
				return 1;
			}
		}
		// printf("test succeeded\n");
		free(array);
		free(copyArray);
	}
	printf("all tests succeeded\n");
	return 0;
}
