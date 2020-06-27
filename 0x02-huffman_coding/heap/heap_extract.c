#include "heap.h"

/**
 * swap - swap data of two nodes
 * @n1: node1
 * @n2: node2
 */
void swap(binary_tree_node_t *n1, binary_tree_node_t *n2)
{
	void *temp;

	temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}

void heapify_down(heap_t *heap);

/**
 * sift_down - heapifies node
 * @heap: heap
 * @node: inserted node
 */
void sift_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;
	if (!node || heap->size < 2)
		return;
	while (node)
	{
		smallest = node;
		if (node->left && heap->data_cmp(smallest->data, node->left->data) > 0)
		{
			smallest = node->left;
		}
		if (node->right && heap->data_cmp(smallest->data, node->right->data) > 0)
		{
			smallest = node->right;
		}
		if (smallest == node)
			break;
		swap(smallest, node);
		node = smallest;
	}
}

/**
 * heap_extract - extracts root node from heap (min value)
 * @heap: heap
 * Return: data of root node
*/
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node;
	void *data;

	if (!heap || !heap->root || heap->size == 0)
		return (NULL);
	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}
	last_node = get_nth_node(heap->root, heap->size);
	heap->root->data = last_node->data;
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;
	free(last_node);
	heap->size -= 1;
	sift_down(heap, heap->root);
	/* heapify_down(heap); */
	return (data);
}
