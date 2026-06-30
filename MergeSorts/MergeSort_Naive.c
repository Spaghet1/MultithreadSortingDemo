#include "mergesort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void merge(int32_t* toArray, int32_t* leftHalf, int32_t* rightHalf, size_t size) {
	size_t leftPtr = 0;
	size_t rightPtr = 0;
	size_t toPtr = 0;
	while (leftPtr < size / 2 && rightPtr < size - size / 2) {
		if (leftHalf[leftPtr] < rightHalf[rightPtr]) toArray[toPtr++] = leftHalf[leftPtr++];
		else toArray[toPtr++] = rightHalf[rightPtr++];
	}
	while (leftPtr < size / 2) toArray[toPtr++] = leftHalf[leftPtr++];
	while (rightPtr < size - size / 2) toArray[toPtr++] = rightHalf[rightPtr++];
}

static void mergeSortHelper(int32_t* array, size_t size) {
	if (size == 1) return;
	int32_t* half1 = malloc(sizeof(int32_t) * (size / 2));
	memcpy(half1, array, sizeof(int32_t) * (size / 2));
	mergeSortHelper(half1, size / 2);
	int32_t* half2 = malloc(sizeof(int32_t) * (size - size / 2));
	memcpy(half2, array + size / 2, sizeof(int32_t) * (size - size / 2));
	mergeSortHelper(half2, size - size / 2);
	merge(array, half1, half2, size);
	free(half1);
	free(half2);
}

void mergeSortNaive(int32_t* array, size_t size) {
	mergeSortHelper(array, size);
}
