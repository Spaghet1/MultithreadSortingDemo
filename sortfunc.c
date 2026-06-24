typedef struct sortFunc {
	char* name;
	void (*func)(int32_t*, uint32_t);
} sortFunc;

static const sortFunc map[] = {
	{"MergeSort_Naive", mergeSortNaive},
	{"MergeSort_2Array", mergeSort2Array},
	{"MergeSort_MultiThreaded", mergeSortMultiThreaded}
};

int findFunc(char* sortName) {
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		if (!strcmp(sortName, map[i].name)) return i;
	}
	return -1;
}

void printFuncs() {
	fprintf(stderr, "Implemented sorts:\n");
	for (unsigned int i = 0; i < sizeof(map) / sizeof(sortFunc); i++) {
		fprintf(stderr, "%s\n", map[i].name);
	}
}
