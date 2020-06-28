#include "huffman.h"

/**
 * huffman_extract_and_insert - creates huffman tree
 * @priority_queue: priority queue which needs to be
 * converted into huffman tree
 * Return: 1 on success or 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new;
	symbol_t *sym;
	int freq = 0;

	/* TODO: do not extract nodes with data == -1 */
	if (!priority_queue || priority_queue->size < 2)
		return (0);
	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);
	if (node1)
		freq += ((symbol_t *)node1->data)->freq;
	if (node2)
		freq += ((symbol_t *)node2->data)->freq;
	sym = symbol_create(-1, freq);
	if (!sym || !freq)
		return (0);
	new = binary_tree_node(NULL, (void *)sym);
	if (!new)
		return (0);
	new->left = node1;
	new->right = node2;
	if (node1)
		node1->parent = new;
	if (node2)
		node2->parent = new;
	if (!heap_insert(priority_queue, (void *)new))
		return (0);
	return (1);
}
