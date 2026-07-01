#include "miscsort.h"
#include <stdlib.h>

int comparator(const void* a, const void* b) {
	return (*(int32_t*)a - *(int32_t*)b);
}

void qsortWrapper(int32_t* array, size_t size) {
	qsort(array, size, sizeof(int32_t), comparator);
}
