#include "heap/heap.h"
#include "huffman.h"
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

void swap_nodes(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *tmp;

	tmp = node1->data;
	node1->data = node2->data;
	node2->data = tmp;
}

typedef struct queue_s
{
	binary_tree_node_t *node;
	struct queue_s *next;
} queue_t;

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

void free_binary_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	free_binary_tree(node->left, free_data);
	free_binary_tree(node->right, free_data);
	if (free_data != NULL)
		free_data(node->data);
	free(node);
}

/**
 * heap_delete - frees a heap struct
 * @heap: a heap structure
 * @free_data: function to state if the data must be freed (no if NULL)
 */
void heap_delete_2(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_binary_tree(heap->root, free_data);
	free(heap);
}

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

int huffman_extract_and_insert_2(heap_t *priority_queue)
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
	left = (binary_tree_node_t *)heap_extract_2(priority_queue);
	right = (binary_tree_node_t *)heap_extract_2(priority_queue);
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
	heap_insert_2(priority_queue, (void *)new_n);
	return (1);
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
	heap_t *heap;
	binary_tree_node_t *tree;

	if (!data || !freq || size == 0)
		return (NULL);
	heap = huffman_priority_queue(data, freq, size);
	if (!heap)
		return (NULL);
	while (heap->size > 1)
	{
		if (!huffman_extract_and_insert(heap))
		{
			/* heap_delete(heap, free_node); */
			/* return (NULL); */
			break;
		}
	}
	tree = heap->root->data;
	free(heap->root);
	free(heap);
	return (tree);
}
