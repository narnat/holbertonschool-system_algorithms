#include "huffman.h"

void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2);
/**
 * struct queue_s - Queue data structure
 * @node: binary tree node
 * @next: pointer to next queue node
 */
typedef struct queue_s
{
	binary_tree_node_t *node;
	struct queue_s *next;
} queue_t;

queue_t *enqueue(queue_t **head, binary_tree_node_t *node);
binary_tree_node_t *dequeue(queue_t **queue);

/**
 * heapify_down - dive the root to its normal place
 * @heap: heap struct
 * if a node has one child it is a left child as a heap is complete
 * beware with cmp, node->data can be a binary_tree_node, so the function
 * will have to go deeper
 */
void heapify_down(heap_t *heap)
{
	binary_tree_node_t *node;

	if (!heap || !heap->root || !(heap->root)->left)
		return;

	node = heap->root;
	while (node->left)
	{
		if (node->right &&
		    heap->data_cmp(node->right->data,
				  node->left->data) < 0 &&
		    heap->data_cmp(node->data,
				  node->right->data) >= 0)
		{
			swap_nodes(node->right, node);
			node = node->right;
			continue;
		}
		else if (heap->data_cmp(node->left->data,
				       node->data) <= 0)
		{
			swap_nodes(node->left, node);
		}
		node = node->left;
	}
}

/**
 * heap_extract - extract the first element of a heap
 * @heap: heap struct
 * Return: data element of the extracted heap node
 */
void *heap_extract_2(heap_t *heap)
{
	queue_t *queue;
	binary_tree_node_t *node;
	void *data;

	if (!heap)
		return (NULL);
	if (!(heap->root))
		return (NULL);
	queue = NULL;
	enqueue(&queue, heap->root);
	while (queue)
	{
		node = dequeue(&queue);
		enqueue(&queue, node->left);
		enqueue(&queue, node->right);
	}
	data = (heap->root)->data;
	if (node == heap->root)
	{
		free(node);
		heap->root = NULL, heap->size = 0;
		return (data);
	}

	if ((node->parent)->left == node)
		(node->parent)->left = NULL;
	else
		(node->parent)->right = NULL;
/*prepare swapping with the root, as we remove the root*/
	swap_nodes(heap->root, node);
	free(node);
	heap->size -= 1;
	heapify_down(heap);
	return (data);
}

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
