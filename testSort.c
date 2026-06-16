#include "MergeSorts/mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 100
#define MAX_SIZE 100

int main() {
	srand(time(NULL));
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		uint32_t size = rand() % MAX_SIZE + 1;
		int32_t* array = malloc(sizeof(int32_t) * (size));
		for (int j = 0; j < size; j++) array[j] = rand();
		mergeSortMultiThreaded(array, size);
		for (int j = 0; j < size - 1; j++) {
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
