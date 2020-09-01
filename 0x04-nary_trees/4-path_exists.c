#include "nary_trees.h"

/**
* path_exists - check if path exists in a tree
* @root: root of a tree
* @path: path to check
* Return: 1 if path exists, 0 if not
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	int idx = 0;
	nary_tree_t const *node;

	if (!root || !path || !path[idx])
		return (0);
	node = root;
	while (node)
	{
		while (node && strcmp(path[idx], node->content))
			node = node->next;
		if (!node)
			return (0);
		node = node->children;
		++idx;
		if (!path[idx])
			break;
	}

	return (!path[idx]);
}
