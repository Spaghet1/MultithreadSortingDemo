CC = gcc
CFLAGS = -g -Wall -Wextra -pthread

SRC_DIRS = MergeSorts Utils MiscSorts
VPATH = $(SRC_DIRS)

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, ObjectFiles/%.o, $(notdir $(SRCS)))

all: benchmark test

test: $(OBJS) ObjectFiles/testsort.o
	$(CC) $(CFLAGS) $^ -o testsort

benchmark: $(OBJS) ObjectFiles/benchmark.o
	$(CC) $(CFLAGS) $^ -o benchmark

obj: $(OBJS)

ObjectFiles/%.o: %.c
	mkdir -p ObjectFiles
	$(CC) $(CFLAGS) -c $< -o $@

ObjectFiles/testsort.o: testsort.c
	mkdir -p ObjectFiles
	$(CC) $(CFLAGS) -c $< -o $@

ObjectFiles/benchmark.o: benchmark.c
	mkdir -p ObjectFiles
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f testsort benchmark

cleanall:
	rm -f testsort benchmark
	rm -r ObjectFiles
	rm  cachegrind*
