#include "MergeSorts/mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 100

int main() {
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		uint32_t size = rand() % 20 + 1;
		int32_t* array = malloc(sizeof(int32_t) * (size));
		for (int j = 0; j < size; j++) array[j] = rand();
		mergeSortNaive(array, size);
		for (int j = 0; j < size - 1; j++) {
			if(array[j] > array[j + 1]) {
				fprintf(stderr, "test failed");
				return 1;
			}
		}
	}
	printf("test succeeded");
	return 0;
}
