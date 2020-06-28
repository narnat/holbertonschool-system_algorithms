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

/**
 * sift_down - heapifies node
 * @heap: heap
 * @node: inserted node
 */
void sift_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *largest;

	if (!node || heap->size < 2)
		return;
	while (node)
	{
		largest = node;
		if (node->left && heap->data_cmp(largest->data, node->left->data) >= 0)
		{
			largest = node->left;
		}
		if (node->right && heap->data_cmp(largest->data, node->right->data) >= 0)
		{
			largest = node->right;
		}
		if (largest == node)
			break;
		swap(largest, node);
		node = largest;
	}
}

void heapify_down(heap_t *heap);

/**
 * heap_extract - extracts root node from heap (min value)
 * @heap: heap
 * Return: data of root node
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last_node;
	void *data;

	if (!heap || !heap->root || heap->size <= 0)
		return (NULL);
	data = heap->root->data;
	last_node = get_nth_node(heap->root, heap->size);
	heap->root->data = last_node->data;
	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}
	else
	{
		heap->root = NULL;
	}
	free(last_node);
	heap->size -= 1;
	/* sift_down(heap, heap->root); */
	heapify_down(heap);
	return (data);
}
