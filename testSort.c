#include "MergeSorts/mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ITERATIONS 1024
#define MAX_SIZE 1024

typedef struct sortFunc {
	char* name;
	void (*func)(int32_t*, uint32_t);
} sortFunc;

static const sortFunc map[] = {
	{"MergeSort_Naive", mergeSortNaive},
	{"MergeSort_2Array", mergeSort2Array},
	{"MergeSort_MultiThreaded", mergeSortMultiThreaded}
};

int findFunc(char* sortName) {
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		if (!strcmp(sortName, map[i].name)) return i;
	}
	return -1;
}
void printFuncs() {
	fprintf(stderr, "Implemented sorts:\n");
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		fprintf(stderr, "%s\n", map[i].name);
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: <EXEC> <SORT>\n");
		printFuncs();
		return 1;
	}
	int funcIndex = findFunc(argv[1]);
	if (funcIndex == -1) {
		printFuncs();
		return 1;
	}
	srand(time(NULL));
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		uint32_t size = MAX_SIZE;
		int32_t* array = malloc(sizeof(int32_t) * (size));
		for (unsigned int j = 0; j < size; j++) array[j] = rand();
		map[funcIndex].func(array, size);
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
