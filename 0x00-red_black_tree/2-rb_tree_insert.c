#include "rb_trees.h"


/**
 * rotate - rotate binary tree either to left or right
 * @node: node to rotate
 * @dir: direction of rotation, LEFT_ROTATE or RIGHT_ROTATE, 0 or 1
 * RIGHT_ROTATE is by default, if passed any non zero value
 */
void rb_tree_insert_recurse(rb_tree_t *root, rb_tree_t *new)
{
	if (!root) return;

	if (new->n < root->n) {
		if (root->left)
		{
			rb_tree_insert_recurse(root->left, new);
			return;
		}
		root->left = new;
		new->parent = root;
		if (root->left) return; /* FIXME: malloc check */
	} else {
		if (root->right)
		{
			rb_tree_insert_recurse(root->right, new);
			return;
		}
		root->right = new;
		new->parent = root;
		if (root->right) return; /* FIXME: malloc check */
	}
}

/**
 * rotate - rotate binary tree either to left or right
 * @node: node to rotate
 * @dir: direction of rotation, LEFT_ROTATE or RIGHT_ROTATE, 0 or 1
 * RIGHT_ROTATE is by default, if passed any non zero value
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new;

	new = rb_tree_node(NULL, value, RED);
	if (!new)
		return (NULL);

	rb_tree_insert_recurse(*tree, new);

	if (!GET_PARENT(new))
		new->color = BLACK;
	return (new);
}

/**
 * rotate - rotate binary tree either to left or right
 * @node: node to rotate
 * @dir: direction of rotation, LEFT_ROTATE or RIGHT_ROTATE, 0 or 1
 * RIGHT_ROTATE is by default, if passed any non zero value
 */
void rotate(rb_tree_t *node, int dir)
{
	rb_tree_t *new = dir == LEFT_ROTATE ? node->right : node->left;
	rb_tree_t *p = GET_PARENT(node);

	if (!new)
		return;

	dir == LEFT_ROTATE ? (node->right = new->left, new->left = node)
		: (node->left = new->right, new->right = node);
	node->parent = new;

	if (dir == LEFT_ROTATE ? node->right : node->left)
		dir == LEFT_ROTATE ? (node->right->parent = node)
			: (node->left->parent = node);

	if (p)
	{
		if (node == p->left)
			p->left = new;
		else if (node == p->right)
			p->right = new;
	}

	new->parent = p;
}
