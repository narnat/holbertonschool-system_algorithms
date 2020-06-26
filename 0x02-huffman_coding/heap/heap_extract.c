#include "heap.h"

/**
 * get_last_node - get the parent where next node should be inserted
 * @node: heap
 * @n: index of node to be inserted
 * Return: parent node which will store the next inserted node
 */
binary_tree_node_t *get_last_node(binary_tree_node_t *node, size_t n)
{
	int index = 0, mask;

	for (index = 0; (1 << (index + 1)) <= (int)n; ++index)
		;
	for (--index; index >= 0; --index)
	{
		mask = 1 << index;
		if (n & mask)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}
	return (node);
}

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
	if (!node || heap->size < 2)
		return;
	while (node)
	{
		if (node->right && node->left &&
		    heap->data_cmp(node->data, node->left->data) > 0 &&
		    heap->data_cmp(node->left->data, node->right->data) < 0)
		{
			swap(node, node->left);
			node = node->left;
		}
		else if (node->right && heap->data_cmp(node->data, node->right->data) > 0)
		{
			swap(node, node->right);
			node = node->right;
		}
		else if (node->left && heap->data_cmp(node->data, node->left->data) > 0)
		{
			swap(node, node->left);
			node = node->left;
		}
		else
		{
				break;
		}
	}
}

binary_tree_node_t *get_last_parent(binary_tree_node_t *node, size_t n);

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
	last_node = get_last_parent(heap->root, heap->size);
	heap->root->data = last_node->data;
	if (last_node->parent->left == last_node)
		last_node->parent->left = NULL;
	else
		last_node->parent->right = NULL;
	free(last_node);
	heap->size -= 1;
	/* sift_down(heap, heap->root); */
	heapify_down(heap);
	return (data);
}
