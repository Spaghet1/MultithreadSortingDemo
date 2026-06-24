#include "MergeSorts/mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
