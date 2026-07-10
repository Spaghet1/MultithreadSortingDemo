#include "mergesort.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

extern int threadDepth;

typedef struct HelperArgs {
	int32_t* fromArray;
	int32_t* toArray;
	size_t left;
	size_t right;
	int depth;
} HelperArgs;

static void merge(int32_t* toArray, int32_t* fromArray, size_t left, size_t right) {
	size_t leftPtr = left;
	size_t rightPtr = (left + right) / 2;
	size_t toPtr = left;
	while (leftPtr < (left + right) / 2 && rightPtr < right) {
		if (fromArray[leftPtr] < fromArray[rightPtr]) toArray[toPtr++] = fromArray[leftPtr++];
		else toArray[toPtr++] = fromArray[rightPtr++];
	}
	while (leftPtr < (left + right) / 2) toArray[toPtr++] = fromArray[leftPtr++];
	while (rightPtr < right) toArray[toPtr++] = fromArray[rightPtr++];
}

static void* mergeSortHelper(void* argPtr) {
	HelperArgs* args = (HelperArgs*) argPtr;
	if (args->left + 1 == args->right) {
		args->toArray[args->left] = args->fromArray[args->left];
		return NULL;
	}
	HelperArgs leftArgs = {
		.fromArray = args->toArray,
		.toArray = args->fromArray,
		.left = args->left,
		.right = (args->left + args->right) / 2,
		.depth = args->depth + 1
	};
	pthread_t leftThread;
	if (leftArgs.depth > threadDepth) mergeSortHelper(&leftArgs);
	else pthread_create(&leftThread, NULL, mergeSortHelper, &leftArgs);
	HelperArgs rightArgs = {
		.fromArray = args->toArray,
		.toArray = args->fromArray,
		.left = (args->left + args->right) / 2,
		.right = args->right,
		.depth = args->depth + 1
	};
	mergeSortHelper(&rightArgs);
	if (leftArgs.depth <= threadDepth) pthread_join(leftThread, NULL);
	merge(args->toArray, args->fromArray, args->left, args->right);
	return NULL;
}

void mergeSortMultiThreaded(int32_t* array, size_t size) {
	int32_t* copyArray = malloc(sizeof(int32_t) * size);
	memcpy(copyArray, array, sizeof(int32_t) * size);
	HelperArgs args = {
		.fromArray = copyArray,
		.toArray = array,
		.left = 0,
		.right = size,
		.depth = 0
	};
	mergeSortHelper(&args);
	free(copyArray);
}
