#include "miscsort.h"

void insertionSort(int32_t* array, size_t size) {
	for (size_t i = 1; i < size; i++) {
		int32_t curr = array[i];
		size_t j = i;
		while (j > 0 && array[j - 1] > curr) {
			array[j] = array[j - 1];
			j--;
		}
		array[j] = curr;
	}
}
