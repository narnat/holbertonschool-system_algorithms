# Nary Trees

CC = gcc
# CC = clang
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3 -ftrapv -Wconversion -Wunreachable-code -Winit-self --std=gnu90

TASK0 = 0-nary_tree_insert
TASK1 = 1-nary_tree_delete
TASK2 = 2-nary_tree_traverse
TASK3 = 3-nary_tree_diameter
TASK4 = 4-path_exists

$(TASK4): $(TASK4).c $(TASK3).c $(TASK2).c $(TASK1).c $(TASK0).c  4-main.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK3): $(TASK3).c $(TASK1).c $(TASK0).c 3-main.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK2): $(TASK2).c $(TASK1).c $(TASK0).c  2-main.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK1): $(TASK1).c $(TASK0).c 1-main.c
	$(CC) $(CFLAGS) -o $@  $^

$(TASK0): $(TASK0).c 0-main.c
	$(CC) $(CFLAGS) -o $@  $^

.PHONY: clean, check, run

clean:
	rm $(TASK0) $(TASK1) $(TASK2) $(TASK3) $(TASK4)

run: $(TASK1)
	@valgrind --leak-check=full ./$^

check:
	betty *.c *.h
