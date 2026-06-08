#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void merge(int32_t* toArray, int32_t* fromArray, uint32_t left, uint32_t right) {
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

void mergeSortHelper(int32_t* toArray, int32_t* fromArray, uint32_t left, uint32_t right) {
	if (left + 1 == right) {
		toArray[left] = fromArray[left];
		return;
	}
	mergeSortHelper(fromArray, toArray, left, (left + right) / 2);
	mergeSortHelper(fromArray, toArray, (left + right) / 2, right);
	merge(toArray, fromArray, left, right);
}

void mergeSort(int32_t* array, uint32_t length) {
	int32_t* copyArray = malloc(sizeof(int32_t) * length);
	memcpy(copyArray, array, sizeof(int32_t) * length);
	mergeSortHelper(array, copyArray, 0, length);
	free(copyArray);
}
