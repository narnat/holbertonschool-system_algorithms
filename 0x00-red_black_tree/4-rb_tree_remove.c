#include "rb_trees.h"


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

rb_tree_t *get_min(rb_tree_t *tree)
{
	while (tree->left)
		tree = tree->left;
	return (tree);
}

rb_tree_t *rb_tree_delete_fix(rb_tree_t *root, rb_tree_t *node)
{
	rb_tree_t *sibling;

	while (node && node != root && node->color == BLACK)
	{
		if (node == node->parent->left)
		{
			sibling = node->parent->right;
			if (sibling && sibling->color == RED)
			{
				sibling->color = BLACK;
				node->parent->color = RED;
				rotate(&root, &(node->parent), LEFT_ROTATE);
				if (node->parent)
					sibling = node->parent->right;
			}
			if ((!sibling->left || sibling->left->color == BLACK)
			    && (!sibling->right || sibling->right->color == BLACK))
			{
				sibling->color = RED;
				node = node->parent;
			}
			else
			{
				if (!sibling->right || sibling->right->color == BLACK)
				{
					if (sibling->left)
						sibling->left->color = BLACK;
					sibling->color = RED;
					rotate(&root, &sibling, RIGHT_ROTATE);
					if (node->parent)
						sibling = node->parent->right;
				}
				sibling->color = node->parent->color;
				if (node->parent)
					node->parent->color = BLACK;
				if (sibling->right)
					sibling->right->color = BLACK;
				rotate(&root, &(node->parent), LEFT_ROTATE);
				node = root;
			}
		}
		else
		{
			sibling = node->parent->left;
			if (sibling && sibling->color == RED)
			{
				sibling->color = BLACK;
				node->parent->color = RED;
				rotate(&root, &(node->parent), RIGHT_ROTATE);
				if (node->parent)
					sibling = node->parent->left;
			}
			if ((!sibling->left || sibling->left->color == BLACK)
			    && (!sibling->right || sibling->right->color == BLACK))
			{
				sibling->color = RED;
				node = node->parent;
			}
			else
			{
				if (!sibling->left || sibling->left->color == BLACK)
				{
					if (sibling->right)
						sibling->right->color = BLACK;
					sibling->color = RED;
					rotate(&root, &sibling, LEFT_ROTATE);
					if (node->parent)
						sibling = node->parent->left;
				}
				sibling->color = node->parent->color;
				if (node->parent)
					node->parent->color = BLACK;
				if (sibling->right)
					sibling->right->color = BLACK;
				rotate(&root, &(node->parent), RIGHT_ROTATE);
				node = root;
			}
		}
	}
	if (node)
		node->color = BLACK;
	return (root);
}

rb_tree_t *rb_tree_delete(rb_tree_t *root, rb_tree_t *del)
{
	rb_tree_t *copy = del, *replace = NULL;
	rb_color_t color = del->color;

	if (!del->left)
	{
		replace = del->right;
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
		if (copy->parent == del && replace && replace->parent)
			replace->parent = copy;
		else
		{
			rb_replace(&root, copy, replace);
			copy->right = del->right;
			if (copy->right)
				copy->right->parent = copy;
		}
		rb_replace(&root, del, copy);
		copy->left = del->left;
		copy->left->parent = copy;
		copy->color = del->color;
	}
	free(del);
	if (color == BLACK)
		return (rb_tree_delete_fix(root, replace));
	return (root);
}

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
