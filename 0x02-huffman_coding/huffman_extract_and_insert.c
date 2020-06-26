#include "huffman.h"

/**
 * huffman_extract_and_insert - extract 2 smallest values from heap, reinsert 1
 * @priority_queue: a min heap priority queue
 * Put in place Huffman compression. Extract 2 least frequent data from heap
 * Reinsert one element in the heap that combines those 2 elements
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *new_n, *left, *right;
	symbol_t *new_s;
	size_t freq;

	if (!priority_queue)
		return (0);

	if (priority_queue->size < 2)
		return (0);

	new_n = malloc(sizeof(binary_tree_node_t));
	if (!new_n)
		return (0);
	new_s = malloc(sizeof(symbol_t));
	if (!new_s)
	{
		free(new_n);
		return (0);
	}
	new_n->data = (void *)new_s;
	left = (binary_tree_node_t *)heap_extract(priority_queue);
	right = (binary_tree_node_t *)heap_extract(priority_queue);
	new_n->left = left;
	if (left)
		left->parent = new_n;
	new_n->right = right;
	if (right)
		right->parent = new_n;
	freq = 0;
	new_n->parent = NULL;
	if (left)
		if (left->data)
			freq += ((symbol_t *)(left->data))->freq;
	if (right)
		if (right->data)
			freq += ((symbol_t *)(right->data))->freq;
	new_s->freq = freq;
	new_s->data = -1;
	heap_insert(priority_queue, (void *)new_n);
	return (1);
}
