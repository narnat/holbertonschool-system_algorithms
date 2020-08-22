#include "nary_trees.h"

/**
 * nary_tree_insert - insert a new child into a tree
 * @parent: parent tree
 * @str: content of a new child
 * Return: NULL if failed, created child if success
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *child;

	child = malloc(sizeof(*child));
	if (!child)
		return (NULL);

	child->content = strdup(str);
	child->children = NULL;
	child->nb_children = 0;

	if (parent)
	{
		child->parent = parent;
		++parent->nb_children;
		child->next = parent->children;
		parent->children = child;
	}
	else
	{
		child->next = child->parent = NULL;
	}
	return (child);
}
