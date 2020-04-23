#include "rb_trees.h"

/**
 * rotate - rotate binary tree either to left or right
 * @tree: RB tree
 * @node: node to rotate
 * @dir: direction of rotation, LEFT_ROTATE or RIGHT_ROTATE, 0 or 1
 * RIGHT_ROTATE is by default, if passed any non zero value
 */
void rotate(rb_tree_t **tree, rb_tree_t **node, int dir)
{
	rb_tree_t *new;
	rb_tree_t *p;

	if (!node || !*node)
		return;

	new = dir == LEFT_ROTATE ? (*node)->right : (*node)->left;
	if (!new)
		return;

	p = GET_PARENT(*node);
	dir == LEFT_ROTATE
		? ((*node)->right = new->left, new->left = (*node))
		: ((*node)->left = new->right, new->right = (*node));
	(*node)->parent = new;
	if (dir == LEFT_ROTATE ? (*node)->right : (*node)->left)
		dir == LEFT_ROTATE
			? ((*node)->right->parent = (*node))
			: ((*node)->left->parent = (*node));
	if (p)
	{
		if ((*node) == p->left)
			p->left = new;
		else if ((*node) == p->right)
			p->right = new;
	}
	else
		*tree = new;
	new->parent = p;
}

/**
 * rb_tree_node - create a new RB node
 * @parent: parent pointer
 * @value: value of node
 * @color: color of the node
 * Return: pointer to the new node, or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);

	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;

	return (new_node);
}
