#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void naiveMerge(int32_t* toArray, int32_t* leftHalf, int32_t* rightHalf, uint32_t size) {
	uint32_t leftPtr = 0;
	uint32_t rightPtr = 0;
	uint32_t toPtr = 0;
	while (leftPtr < size / 2 && rightPtr < size - size / 2) {
		if (leftHalf[leftPtr] < rightHalf[rightPtr]) toArray[toPtr++] = leftHalf[leftPtr++];
		else toArray[toPtr++] = rightHalf[rightPtr++];
	}
	while (leftPtr < size / 2) toArray[toPtr++] = leftHalf[leftPtr++];
	while (rightPtr < size - size / 2) toArray[toPtr++] = rightHalf[rightPtr++];
}

void naiveMergeSortHelper(int32_t* array, uint32_t size) {
	if (size == 1) return;
	int32_t* half1 = malloc(sizeof(int32_t) * size / 2);
	memcpy(half1, array, sizeof(int32_t) * size / 2);
	naiveMergeSortHelper(half1, size / 2);
	int32_t* half2 = malloc(sizeof(int32_t) * (size - size / 2));
	memcpy(half2, array + size / 2, sizeof(int32_t) * (size - size / 2));
	naiveMergeSortHelper(half2, size - size / 2);
	naiveMerge(array, half1, half2, size);
	free(half1);
	free(half2);
}

void naiveMergeSort(int32_t* array, uint32_t length) {
	naiveMergeSortHelper(array, length);
}
