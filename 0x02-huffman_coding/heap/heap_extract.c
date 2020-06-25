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

	for (index = 0; (1 << (index + 1)) < (int)n; index++)
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
 * sift_down - heapifies node
 * @heap: heap
 * @node: inserted node
 */
void sift_down(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	if (!node)
		return;
	while (node)
	{
		if (node->left && heap->data_cmp(node->data, node->left->data) > 0)
		{
			temp = node->data;
			node->data = node->left->data;
			node->left->data = temp;
			node = node->left;
		}
		else if (node->right && heap->data_cmp(node->data, node->right->data) > 0)
		{
			temp = node->data;
			node->data = node->right->data;
			node->right->data = temp;
			node = node->right;
		}
		else
		{
			break;
		}
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

	if (!heap || !heap->root)
		return (NULL);
	data = heap->root->data;
	last_node = get_last_node(heap->root, heap->size);
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
	sift_down(heap, heap->root);
	return (data);
}
