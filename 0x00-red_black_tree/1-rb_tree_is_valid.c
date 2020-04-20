#include "rb_trees.h"
#include <limits.h>
/**
 * rb_tree_verify - verify Red Black tree properties
 * @tree: root of the binary tree
 * @min_val: min val
 * @max_val: max val
 * @height: black height of RB tree
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_verify(const rb_tree_t *tree, int min_val,
		   int max_val, ssize_t *height)
{
	ssize_t lheight, rheight;

	if (!tree)                   /*Property #3 */
	{
		*height = 1;
		return (1);
	}

	if (tree->color == RED)        /*Property #4 */
	{
		if ((tree->left && tree->color == RED)
		    || (tree->right && tree->color == RED))
		{
			*height = -1;
			return (0);
		}
	}

	if (tree->n < min_val || tree->n > max_val)  /* Check if it is BST */
	{
		return (0);
	}

	if (!rb_tree_verify(tree->left, min_val, tree->n, &lheight))
		return (0);

	if (!rb_tree_verify(tree->right, tree->n, max_val, &rheight))
		return (0);

	if (lheight != rheight)       /* Property #5 */
		return (0);

	*height = lheight + tree->color == BLACK ? 1 : 0;

	printf("L: %ld    R: %ld H: %ld\n", lheight, rheight, *height);

	return (1);
}

/**
 * rb_tree_is_valid - verify Red Black tree properties
 * @tree: root of the binary tree
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	ssize_t heigth;

	/* Property #2 of RB trees*/
	if (!tree || (!tree->parent && tree->color != BLACK))
		return (0);
	return (rb_tree_verify(tree, INT_MIN, INT_MAX, &heigth));
}
