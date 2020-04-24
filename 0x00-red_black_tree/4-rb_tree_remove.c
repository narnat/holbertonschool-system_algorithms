#include "rb_trees.h"

/**
 * rb_replace - Put @new to into place of @old
 * @tree: RB tree
 * @old: old node
 * @new: new node
*/
void rb_replace(rb_tree_t **tree, rb_tree_t *old, rb_tree_t *new)
{
	if (old->parent == NULL)
		*tree = new;
	else if (old == old->parent->left)
		old->parent->left = new;
	else
		old->parent->right = new;
	if (new)
		new->parent = old->parent;
}

/**
 * get_min - get min in BST tree
 * @tree: RB tree
 * Return: node with min value
 */
rb_tree_t *get_min(rb_tree_t *tree)
{
	while (tree->left)
		tree = tree->left;
	return (tree);
}

/**
 * rb_fix_left_sibling - fix left sibling
 * @root: RB tree
 * @node: node which breaks properties of RB tree
 * @parent: parent of @node or if @node is null, it is
 * a node where RB is invalid
 * Return: Updated @node
 */
rb_tree_t *rb_fix_left_sibling(rb_tree_t **root,
			       rb_tree_t *node, rb_tree_t *parent)
{
	rb_tree_t *sibling;

	sibling = parent->left;
	if (sibling && sibling->color == RED)
	{
		sibling->color = BLACK;
		parent->color = RED;
		rotate(root, &(parent), RIGHT_ROTATE);
		if (parent)
			sibling = parent->left;
	}
	if ((!sibling->left || sibling->left->color == BLACK)
	    && (!sibling->right || sibling->right->color == BLACK))
	{
		sibling->color = RED;
		node = parent;
	}
	else
	{
		if (!sibling->left || sibling->left->color == BLACK)
		{
			if (sibling->right)
				sibling->right->color = BLACK;
			sibling->color = RED;
			rotate(root, &sibling, LEFT_ROTATE);
			if (parent)
				sibling = parent->left;
		}
		if (sibling)
			sibling->color = parent->color;
		parent->color = BLACK;
		if (sibling && sibling->left)
			sibling->left->color = BLACK;
		rotate(root, &parent, RIGHT_ROTATE);
		node = *root;
	}
	return (node);
}

/**
 * rb_fix_right_sibling - fix right sibling
 * @root: RB tree
 * @node: node which breaks properties of RB tree
 * @parent: parent of @node or if @node is null, it is
 * a node where RB is invalid
 * Return: Updated @node
*/
rb_tree_t *rb_fix_right_sibling(rb_tree_t **root,
				rb_tree_t *node, rb_tree_t *parent)
{
	rb_tree_t *sibling;

	sibling = parent->right;
	if (sibling && sibling->color == RED)
	{
		sibling->color = BLACK;
		parent->color = RED;
		rotate(root, &parent, LEFT_ROTATE);
		if (parent)
			sibling = parent->right;
	}
	if ((!sibling->left || sibling->left->color == BLACK)
	    && (!sibling->right || sibling->right->color == BLACK))
	{
		sibling->color = RED;
		node = parent;
	}
	else
	{
		if (!sibling->right || sibling->right->color == BLACK)
		{
			if (sibling->left)
				sibling->left->color = BLACK;
			sibling->color = RED;
			rotate(root, &sibling, RIGHT_ROTATE);
			if (parent)
				sibling = parent->right;
		}
		if (sibling)
			sibling->color = parent->color;
		parent->color = BLACK;
		if (sibling && sibling->right)
			sibling->right->color = BLACK;
		rotate(root, &parent, LEFT_ROTATE);
		node = *root;
	}

	return (node);
}

/**
 * rb_tree_delete_fix - fix RB tree after deletion of a node
 * @root: RB tree
 * @node: node which breaks properties of RB tree
 * @parent: parent of @node or if @node is null, it is
 * a node where RB is invalid
 * Return: Updated @root
 */
rb_tree_t *rb_tree_delete_fix(rb_tree_t *root,
			      rb_tree_t *node, rb_tree_t *parent)
{
	while ((node && node != root && node->color == BLACK) || (!node && parent))
	{
		if (node == parent->left)
		{
			node = rb_fix_right_sibling(&root, node, parent);
			parent = GET_PARENT(node);
		}
		else
		{
			node = rb_fix_left_sibling(&root, node, parent);
			parent = GET_PARENT(node);
		}
	}
	if (node)
		node->color = BLACK;
	return (root);
}

/**
 * rb_tree_delete - Delete a node @del from @root
 * @root: RB tree
 * @del: node which will be deleted
 * Return: Updated @root
*/
rb_tree_t *rb_tree_delete(rb_tree_t *root, rb_tree_t *del)
{
	rb_tree_t *copy = del, *replace = NULL, *parent = NULL;
	rb_color_t color = del->color;

	if (!del->left)
	{
		replace = del->right; /* FIXME: it can be null*/
		!replace ? parent = del->parent : NULL;
		rb_replace(&root, del, replace);
	}
	else if (!del->right)
	{
		replace = del->left;
		rb_replace(&root, del, replace);
	}
	else
	{
		copy = get_min(del->right);
		color = copy->color;
		replace = copy->right;
		if (copy->parent == del) /* FIXME: bug*/
		{
			replace ? replace->parent = copy : NULL;
			parent = copy;
		}
		else
		{
			rb_replace(&root, copy, copy->right);
			parent = copy->parent;
			copy->right = del->right;
			copy->right ? copy->right->parent = copy : NULL;
		}
		rb_replace(&root, del, copy);
		copy->left = del->left;
		copy->left->parent = copy;
		copy->color = del->color;
	}
	free(del);
	if (color == BLACK)
		return (rb_tree_delete_fix(root, replace, parent));
	return (root);
}

/**
 * rb_tree_remove - remove a node from RB tree
 * @root: RB tree
 * @n: value which needs to be deleted
 * Return: updated @root
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *cur = root;

	while (cur)
	{
		if (cur->n == n)
			break;
		else if (cur->n < n)
			cur = cur->right;
		else
			cur = cur->left;
	}

	if (!cur)
		return (root);

	return (rb_tree_delete(root, cur));
}
