#ifndef HUFFMAN_H
#define HUFFMAN_H


#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
void heap_free(heap_t *heap, void (*free_data)(void *));
void free_node(void *p);
#endif /* HUFFMAN_H */
