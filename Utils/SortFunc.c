#include <string.h>
#include <stdio.h>
#include "../MergeSorts/mergesort.h"
#include "SortFunc.h"

typedef struct sortFunc {
	char* name;
	void (*func)(int32_t*, size_t);
} sortFunc;

static const sortFunc map[] = {
	{"MergeSort_Naive", mergeSortNaive},
	{"MergeSort_2Array", mergeSort2Array},
	{"MergeSort_MultiThreaded", mergeSortMultiThreaded}
};

void (*findFunc(char* sortName))(int32_t*, size_t) {
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		if (!strcmp(sortName, map[i].name)) return map[i].func;
	}
	return NULL;
}

void printFuncs() {
	fprintf(stderr, "Implemented sorts:\n");
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		fprintf(stderr, "%s\n", map[i].name);
	}
}
