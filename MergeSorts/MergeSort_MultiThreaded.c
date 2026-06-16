#include "mergesort.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct HelperArgs {
	int32_t* fromArray;
	int32_t* toArray;
	uint32_t left;
	uint32_t right;
} HelperArgs;

static void merge(int32_t* toArray, int32_t* fromArray, uint32_t left, uint32_t right) {
	uint32_t leftPtr = left;
	uint32_t rightPtr = (left + right) / 2;
	uint32_t toPtr = left;
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
	};
	pthread_t leftThread;
	pthread_create(&leftThread, NULL, mergeSortHelper, &leftArgs);
	HelperArgs rightArgs = {
		.fromArray = args->toArray,
		.toArray = args->fromArray,
		.left = (args->left + args->right) / 2,
		.right = args->right,
	};
	mergeSortHelper(&rightArgs);
	pthread_join(leftThread, NULL);
	merge(args->toArray, args->fromArray, args->left, args->right);
	return NULL;
}

void mergeSortMultiThreaded(int32_t* array, uint32_t size) {
	int32_t* copyArray = malloc(sizeof(int32_t) * size);
	memcpy(copyArray, array, sizeof(int32_t) * size);
	HelperArgs args = {
		.fromArray = copyArray,
		.toArray = array,
		.left = 0,
		.right = size,
	};
	mergeSortHelper(&args);
	free(copyArray);
}
