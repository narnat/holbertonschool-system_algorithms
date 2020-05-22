CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c89 -ggdb3

TASK0 = 0-graph_create
TASK1 = 1-graph_add_vertex
TASK2 = 2-graph_add_edge
TASK3 = 3-graph_delete
TASK4 = 4-depth_first_traverse
TASK5 = 5-breadth_first_traverse


# $(TASK5): $(TASK5).c 5-main.c
# 	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

# $(TASK4): $(TASK4).c 4-main.c
# 	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

# $(TASK3): $(TASK3).c 3-main.c
# 	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

# $(TASK2): $(TASK2).c 2-main.c
# 	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

# $(TASK1): $(TASK1).c 1-main.c
# 	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

$(TASK0): $(TASK0).c 0-main.c
	$(CC) $(CFLAGS) -o $@  $^ graph_display.c

.PHONY: clean, check

clean:
	rm $(TASK0) $(TASK1) $(TASK2) $(TASK3) $(TASK4) $(TASK5) $(TASK6)

check:
	betty *.c *.h
