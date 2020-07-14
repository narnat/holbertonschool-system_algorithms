CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3 -lm

TASK0 = 0-backtracking_array
TASK1 = 1-backtracking_graph
TASK2 = 2-dijkstra_graph
TASK3 = 100-a_star_graph

$(TASK3): $(TASK3).c 100-main.c libqueues.a libgraphs.a
	$(CC) $(CFLAGS) -o $@  $^

$(TASK2): $(TASK2).c 2-main.c libqueues.a libgraphs.a
	$(CC) $(CFLAGS) -o $@  $^

$(TASK1): $(TASK1).c 1-main.c libqueues.a libgraphs.a
	$(CC) $(CFLAGS) -o $@  $^

$(TASK0): $(TASK0).c 0-main.c libqueues.a
	$(CC) $(CFLAGS) -o $@  $^

.PHONY: clean, check, run

clean:
	rm $(TASK0) $(TASK1) $(TASK2) $(TASK3)

run: $(TASK3)
	@valgrind --leak-check=full ./$^

check:
	betty *.c *.h
