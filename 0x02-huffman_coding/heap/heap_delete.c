#include "heap.h"

/**
 * free_tree - free binary heap
 * @root: root
 * @free_data: function to free nodes
 */
void free_tree(binary_tree_node_t *root, void (*free_data)(void *))
{
	if (!root)
		return;
	free_tree(root->left, free_data);
	free_tree(root->right, free_data);
	if (free_data)
		free_data(root->data);
	free(root);
}

/**
 * heap_delete - deletes heap
 * @heap: heap
 * @free_data: function to free nodes
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;
	free_tree(heap->root, free_data);
	free(heap);
}
