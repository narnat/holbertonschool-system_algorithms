#include "heap/heap.h"
#include "huffman.h"

/**
 * free_data - frees a node in a heap
 * @p: should be a binary_tree_node
 * Free a tree of binary_tree_node containing symbol values
 */
void free_data(void *p)
{
	binary_tree_node_t *tmp;

	if (!p)
		return;
	tmp = (binary_tree_node_t *)p;

	free_data((void *)tmp->left);
	free_data((void *)tmp->right);
	if (tmp->data)
		free(tmp->data);
	free(tmp);
}

/**
 * huffman_tree - builds a Huffman tree
 * @data: array of character
 * @freq: frequencies of each character of @data
 * @size: size of @freq and @data
 * Return: Huffman tree if success, NULL on failure
*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	heap_t *heap;
	int result;

	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);

	while (heap->size > 1)
	{
		result = huffman_extract_and_insert(heap);
		if (result == 0)
			break;
	}
	root = (binary_tree_node_t *)heap_extract(heap);
	heap_delete(heap, free_data);
	return (root);
}
/* binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size) */
/* { */
/*	heap_t *heap; */
/*	binary_tree_node_t *tree; */

/*	/\* if (!data || !freq || size == 0) *\/ */
/*	/\*	return (NULL); *\/ */
/*	heap = huffman_priority_queue(data, freq, size); */
/*	if (!heap) */
/*		return (NULL); */
/*	while (heap->size > 1) */
/*	{ */
/*		if (!huffman_extract_and_insert(heap)) */
/*		{ */
/*			/\* heap_delete(heap, free_node); *\/ */
/*			/\* return (NULL); *\/ */
/*			break; */
/*		} */
/*	} */
/*	tree = heap->root->data; */
/*	free(heap->root); */
/*	free(heap); */
/*	return (tree); */
/* } */
