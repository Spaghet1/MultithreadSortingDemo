CC = gcc
CFLAGS = -g -Wall -Wextra -pthread

SRC_DIRS = MergeSorts
VPATH = $(SRC_DIRS)

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c, ObjectFiles/%.o, $(notdir $(SRCS)))

test: $(OBJS) ObjectFiles/testSort.o
	$(CC) $(CFLAGS) $^ -o testSort

obj: $(OBJS)

ObjectFiles/%.o: %.c
	mkdir -p ObjectFiles
	$(CC) $(CFLAGS) -c $< -o $@

ObjectFiles/testSort.o: testSort.c
	mkdir -p ObjectFiles
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm testSort
