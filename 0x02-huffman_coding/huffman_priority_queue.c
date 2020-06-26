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

/*heapify or percolate up a node in a min heap*/
/**
 * heapify_min - percolate up in a min heap
 * @heap: heap structure
 * @node: node just inserted
 * Return: pointer to the node bearing the newly added data
 */
binary_tree_node_t *heapify_min(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *to_return;

	to_return = node;
	while (node->parent)
	{
		if (heap->data_cmp(node->parent->data, node->data) > 0)
		{
			swap_nodes(node, node->parent);
/*to_return = node;*/
		}
		node = node->parent;
	}
/*heap->root = node;*/
	return (to_return);
}

/**
 * binary_tree_node - create a heap node
 * @parent: parent node of the node to be created
 * @data: data to store in the node
 * Return: pointer to created node or NULL
 */
binary_tree_node_t *binary_tree_node_2(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new;

	new = malloc(sizeof(binary_tree_node_t));
	if (!new)
		return (NULL);

	new->data = data;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	if (parent)
	{
		if (parent->left == NULL)
		{
			parent->left = new;
		}
		else if (parent->right == NULL)
		{
			parent->right = new;
		}
		else
		{
			free(new);
			new = NULL;
		}
	}
	return (new);
}

/**
 * heap_insert - insert a node in a min heap
 * @heap: pointer to heap structure
 * @data: data to insert in the heap
 * Return: pointer to the created node or NULL
 */
binary_tree_node_t *heap_insert_2(heap_t *heap, void *data)
{
	binary_tree_node_t *new, *node;
	queue_t *queue, *tmp;

	if (!heap)
		return (NULL);
	queue = NULL;
	if (heap->root == NULL)
	{
		new = binary_tree_node_2(NULL, data);
		if (!new)
			return (NULL);
		heap->root = new;
		heap->size = 1;
		return (new);
	}
	queue = NULL;
	enqueue(&queue, heap->root);
	while (queue)
	{
		node = dequeue(&queue);
		if (node->right)
		{
			enqueue(&queue, node->left);
			enqueue(&queue, node->right);
		}
		else
		{
			while (queue)
			{
				tmp = queue;
				queue = queue->next;
				free(tmp);
			}
		}
	}
	new = binary_tree_node_2(node, data);
	if (!new)
		return (NULL);
	heap->size += 1;
	return (heapify_min(heap, new));
}

/**
 * freq_cmp - compare the frequencies of 2 symbol_t
 * @v1: first symbol
 * @v2: second symbol
 * This function belongs to the heap. It works if the heap
 * stores binary_tree_nodes which themselves store symbol_t
 *
 * Return: difference in frequency
 */
int freq_cmp(void *v1, void *v2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	if (!v1 || !v2)
		return (-666);

	n1 = (binary_tree_node_t *)v1;
	n2 = (binary_tree_node_t *)v2;
	s1 = (symbol_t *)(n1->data);
	s2 = (symbol_t *)(n2->data);
	return (s1->freq - s2->freq);
}

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
 * huffman_priority_queue - create a min heap with arrays of data and freq
 * @data: data to store in a priority queue
 * @freq: frequency associated with each data
 * @size: size of data and freq arrays
 * Return: pointer to the created min heap or NULL
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	size_t i;
	heap_t *heap;
	symbol_t *new;
	binary_tree_node_t *node;

	if (!data || !freq || size <= 0)
		return (NULL);

	heap = heap_create(freq_cmp);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; ++i)
	{
		if (freq[i] == 0)
			continue;
		new = symbol_create(data[i], freq[i]);
		if (!new)
		{
			heap_delete(heap, free_data);
			return (NULL);
		}
		node = binary_tree_node(NULL, (void *)new);
		if (!node)
		{
			free(new);
			heap_delete(heap, free_data);
			return (NULL);
		}
		heap_insert(heap, (void *)node);
	}
	return (heap);
}
