#include "huffman.h"

/**
 * swap_nodes - swap 2 nodes values
 * @node1: node to swap
 * @node2: node to swap
 */
void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *tmp;

	tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}

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


/*prepare level order traversal: queue functions*/
/**
 * free_queue - free a queue
 * @head: head of queue
 */
void free_queue(queue_t **head)
{
	queue_t *tmp;

	if (!head)
		return;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

/**
 * enqueue - enqueue an element
 * @head: head of queue
 * @node: node to insert in the end
 * Return: pointer to created node
 */
queue_t *enqueue(queue_t **head, binary_tree_node_t *node)
{
	queue_t *new, *tmp;

	if (!head || !node)
		return (NULL);
	new =  malloc(sizeof(queue_t));
	if (!new)
	{
		free_queue(head);
		return (NULL);
	}
	new->node = node;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

/**
 * dequeue - pop an element from a queue
 * @queue: pointer to a queue head
 * Return: the value of the popped node
 */
binary_tree_node_t *dequeue(queue_t **queue)
{
	queue_t *first;
	binary_tree_node_t *node;

	if (!queue || !*queue)
		return (NULL);

	first = *queue;
	*queue = first->next;
	node = first->node;
	free(first);
	return (node);
}


void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2);
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
	if (!sym)
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
