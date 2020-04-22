#include "rb_trees.h"

/**
 * array_to_rb_tree - Convert array to RB tree, O(nlogn) time complexity
 * @array: array to be converted to RB tree
 * @size: size of the array
 * Return: new RB tree consturcted from @array
*/
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *root = NULL;
	size_t i;

	if (!array)
		return (NULL);

	for (i = 0; i < size; ++i)
	{
		rb_tree_insert(&root, array[i]);
	}

	return (root);
}
