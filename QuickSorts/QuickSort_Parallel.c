#include "quicksort.h"
#include "stdint.h"
#include <pthread.h>

extern int threadDepth;

typedef struct HelperArgs {
	int32_t* array;
	size_t size;
	int depth;
} HelperArgs;

static inline void swap(int32_t* array, size_t a, size_t b) {
	int32_t temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void* quickSortParallelHelper(void* argPtr) {
	HelperArgs* args = (HelperArgs*) argPtr;
	if (args->size <= 1) return NULL;
	int32_t pivot = args->array[args->size - 1];
	size_t left = 0;
	for (size_t right = 0; right < args->size; right++) {
		if (args->array[right] <= pivot) {
			swap(args->array, left++, right);
		}
	}
	pthread_t leftThread;
	HelperArgs leftArgs = {
		.array = args->array,
		.size = left - 1,
		.depth = args->depth + 1
	};
	if (args->depth < threadDepth) pthread_create(&leftThread, NULL, quickSortParallelHelper, &leftArgs);
	else quickSortParallelHelper(&leftArgs);
	HelperArgs rightArgs = {
		.array = args->array + left,
		.size = args->size - left,
		.depth = args->depth + 1
	};
	quickSortParallelHelper(&rightArgs);
	if (args->depth < threadDepth) pthread_join(leftThread, NULL);
	return NULL;
}

void quickSortParallel(int32_t* array, size_t size) {
	HelperArgs args = {
		.array = array,
		.size = size,
		.depth = 0
	};
	quickSortParallelHelper(&args);
}
