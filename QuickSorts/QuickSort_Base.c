#include "quicksort.h"
#include "stdint.h"

static inline void swap(int32_t* array, size_t a, size_t b) {
	int32_t temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void quickSortBase(int32_t* array, size_t size) {
	if (size <= 1) return;
	int32_t pivot = array[size - 1];
	size_t left = 0;
	for (size_t right = 0; right < size; right++) {
		if (array[right] <= pivot) {
			swap(array, left++, right);
		}
	}
	quickSortBase(array, left - 1);
	quickSortBase(array + left, size - left);
}
