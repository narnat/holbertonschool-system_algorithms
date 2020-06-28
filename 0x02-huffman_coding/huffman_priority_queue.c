#include "heap/heap.h"
#include "huffman.h"

/**
 * node_cmp - compare function for heap nodes
 * @d1: data from first node
 * @d2: data from second node
 * Return: difference between frequencies of characters
*/
int node_cmp(void *d1, void *d2)
{
	binary_tree_node_t *node1 = d1, *node2 = d2;
	symbol_t *sym1, *sym2;

	if (!node1)
		return (-1);
	sym1 = node1->data;
	if (!node2)
		return (1);
	sym2 = node2->data;
	return (sym1->freq - sym2->freq);
}

/**
 * free_node - frees node of priority queue
 * @p: node
 */
void free_node(void *p)
{
	binary_tree_node_t *node1, *node2;

	if (!p)
		return;
	(void) node2;
	node1 = p;
	/* node2 = node1->data; */
	/* free(node2->data); */
	/* free(node2); */
	free(node1);
}

/**
 * huffman_priority_queue - creates priority queue
 * @data: array of characters
 * @freq: array of frequencies of characters
 * @size: sizeof @freq and @data
 * Return:  pointer to the created min heap (also called priority queue)
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	size_t i;
	symbol_t *sym;
	binary_tree_node_t *node;

	if (!data || !freq || size == 0)
		return (NULL);
	heap = heap_create(node_cmp);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; ++i)
	{
		if (freq[i] == 0)
			continue;
		sym = symbol_create(data[i], freq[i]);
		if (!sym)
		{
			heap_delete(heap, free_node);
			return (NULL);
		}
		node = binary_tree_node(NULL, (void *)sym);
		if (!node || !heap_insert(heap, (void *)node))
		{
			free(sym);
			free(node);
			heap_delete(heap, free_node);
			return (NULL);
		}
	}
	return (heap);
}
