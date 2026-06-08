#include "mergesort.c"
#include <stdio.h>

int main() {
	int32_t array[] = {20, 10, 2, 5, 34, 1, 0, -20, 500};
	mergeSort(array, sizeof(array) / sizeof(int32_t));
	for (int i = 0; i < sizeof(array) / sizeof(int32_t); i++) printf("%d ", array[i]);
}
