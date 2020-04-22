#include "rb_trees.h"

/**
 * right_side_fix - Case where parent of @node is at
 * the right side of its grandparent
 * @tree: RB tree
 * @node: node to be fixed
 * Return: updated pointer to node
 */
rb_tree_t *right_side_fix(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent, *uncle, *gparent;

	parent = GET_PARENT(node);
	gparent = GET_GRANDPARENT(node);
	uncle = gparent->left;
	if (uncle && uncle->color == RED)
	{
		uncle->color = parent->color = BLACK;
		gparent->color = RED;
		node = gparent;
	}
	else
	{
		if (parent->left == node)
		{
			node = parent;
			rotate(tree, &node, RIGHT_ROTATE);
			parent = GET_PARENT(node);
			gparent = GET_GRANDPARENT(node);
		}
		parent->color = BLACK;
		if (gparent)
		{
			gparent->color = RED;
			rotate(tree, &gparent, LEFT_ROTATE);
		}
	}

	return (node);
}

/**
 * left_side_fix - Case where parent of @node is at
 * the left side of its grandparent
 * @tree: RB tree
 * @node: node to be fixed
 * Return: updated pointer to node
 */
rb_tree_t *left_side_fix(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent, *uncle, *gparent;

	parent = GET_PARENT(node);
	gparent = GET_GRANDPARENT(node);
	uncle = gparent->right;
	if (uncle && uncle->color == RED)
	{
		uncle->color = parent->color = BLACK;
		gparent->color = RED;
		node = gparent;
	}
	else
	{
		if (parent->right == node)
		{
			node = parent;
			rotate(tree, &node, LEFT_ROTATE);
			parent = GET_PARENT(node);
			gparent = GET_GRANDPARENT(node);
		}
		parent->color = BLACK;
		if (gparent)
		{
			gparent->color = RED;
			rotate(tree, &gparent, RIGHT_ROTATE);
		}
	}

	return (node);
}

/**
 * rb_tree_fix - fix RB tree
 * @tree: RB tree
 * @node: the newly inserted node
 */
void rb_tree_fix(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *parent = GET_PARENT(node), *gparent = GET_GRANDPARENT(node);

	while (parent && parent->color == RED)
	{
		if (gparent && gparent->left == parent)
			node = left_side_fix(tree, node);
		else
			node = right_side_fix(tree, node);

		parent = GET_PARENT(node);
		gparent = GET_GRANDPARENT(node);
	}
	(*tree)->color = BLACK;
}

/**
 * rb_tree_insert - insert into RB tree
 * @tree: RB tree
 * @value: value to put into @tree
 * Return: a new node with @value or NULL in case of failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new = NULL, *cur = NULL, *prev = NULL;

	if (!tree)
		return (NULL);
	cur = *tree;
	new = rb_tree_node(NULL, value, RED);
	if (!new)
		return (NULL);
	while (cur)
	{
		prev = cur;
		if (cur->n == new->n)
			return (free(new), NULL);
		if (new->n < cur->n)
			cur = cur->left;
		else
			cur = cur->right;
	}
	new->parent = prev;
	if (!prev)
		*tree = new;
	else if (new->n < prev->n)
		prev->left = new;
	else
		prev->right = new;
	rb_tree_fix(tree, new);
	return (new);
}

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
