#include "heap.h"

/**
 * binary_tree_node - creates a node
 * @parent: parent node
 * @data: data for the node
 * Return: a pointer to the created node or NULL if it fails
*/
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node;

	node = calloc(sizeof(*node), 1);
	if (!node)
		return (NULL);
	node->data = data;
	node->parent = parent;
	return (node);
}
