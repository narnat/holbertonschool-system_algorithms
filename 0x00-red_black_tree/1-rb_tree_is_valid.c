#include "rb_trees.h"
#include <limits.h>

/**
 * rb_tree_verify - verify Red Black tree properties
 * @tree: root of the binary tree
 * @min_val: min val
 * @max_val: max val
 * @h: black height of RB tree
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_verify(const rb_tree_t *tree, int min_val, int max_val, int *h)
{
	int lh = 0, rh = 0;

	if (!tree)                   /*Property #3 */
	{
		*h = 1;
		return (1);
	}
	if (tree->color == RED)        /*Property #4 */
		if ((tree->left && tree->left->color == RED)
		    || (tree->right && tree->right->color == RED))
			return (0);
	if (tree->n < min_val || tree->n > max_val)  /* Check if it is BST */
		return (0);
	if (!rb_tree_verify(tree->left, min_val, tree->n, &lh))
		return (0);
	if (!rb_tree_verify(tree->right, tree->n, max_val, &rh))
		return (0);
	*h = lh + (tree->color == BLACK ? 1 : 0);

	return (lh == rh);
}

/**
 * rb_tree_is_valid - verify Red Black tree properties
 * @tree: root of the binary tree
 * Return: 1 if tree is a valid Red-Black Tree, and 0 otherwise
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int res, h = 0;

	/* Property #2 of RB trees*/
	if (!tree || (!tree->parent && tree->color != BLACK))
		return (0);
	res = rb_tree_verify(tree, INT_MIN, INT_MAX, &h);
	printf("Max Heigth: %d, is valid: %d\n", h, res);
	return (res);
}
