CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3 -std=gnu90 -lm

TASK0 = 0-backtracking_array
TASK1 = 1-backtracking_graph

$(TASK1): $(TASK1).c 1-main.c libqueues.a libgraphs.a
	$(CC) $(CFLAGS) -o $@  $^

$(TASK0): $(TASK0).c 0-main.c libqueues.a
	$(CC) $(CFLAGS) -o $@  $^

.PHONY: clean, check, run

clean:
	rm $(TASK0) $(TASK1) $(TASK2) $(TASK3) $(TASK4) $(TASK5) $(TASK6)

run: $(TASK1)
	@valgrind -q --leak-check=full ./$^

check:
	betty *.c *.h
