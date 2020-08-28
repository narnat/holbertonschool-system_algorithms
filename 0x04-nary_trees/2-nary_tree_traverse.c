#include "nary_trees.h"

size_t ntree_traverse(nary_tree_t const *root, void
					  (*action)(nary_tree_t const *node, size_t depth),
					  size_t depth)
{
	nary_tree_t const *node;
	size_t max = 0, ret;

	if (!root)
		return (0);
	node = root;
	while (node)
	{
		action(node, depth);
		ret = ntree_traverse(node->children, action, depth + 1);
		if (max < ret)
			max = ret;
		node = node->next;
	}
	return (1 + max);
}

size_t nary_tree_traverse(nary_tree_t const *root, void
						  (*action)(nary_tree_t const *node, size_t depth))
{
	size_t depth;

	if (!root || !action)
		return (0);
	depth = ntree_traverse(root, action, 0);
	return (depth);
}
