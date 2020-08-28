#include "nary_trees.h"

/**
 * nary_tree_delete - deletes a tree
 * @tree: tree to be deleted
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *tmp;

	while (tree)
	{
		tmp = tree;
		tree = tree->next;
		free(tmp->content);
		nary_tree_delete(tmp->children);
		free(tmp);
	}
}
