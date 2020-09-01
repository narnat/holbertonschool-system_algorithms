#include "nary_trees.h"

/**
* max_depth - gets the max depth of a tree
* @root: root of a tree
* @diameter: max diameter so far
* Return: max depth of a tree
*/
size_t max_depth(nary_tree_t const *root, size_t *diameter)
{
	size_t max1 = 0, max2 = 0, ret;
	nary_tree_t *child;

	if (!root)
		return (0);
	for (child = root->children; child; child = child->next)
	{
		ret = max_depth(child, diameter);
		if (max1 < ret)
		{
			max2 = max1;
			max1 = ret;
		}
		else if (max2 < ret)
			max2 = ret;
	}
	*diameter = MAX(*diameter, max1 + max2);
	return (1 + max1);
}

/**
* nary_tree_diameter - gets diameter of a tree
* @root: root of a tree
* Return: diameter of a tree
*/
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	max_depth(root, &diameter);
	return (diameter + 1);
}
