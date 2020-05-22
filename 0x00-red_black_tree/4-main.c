#include "rb_trees.h"

rb_tree_t *valid_rb(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 98, BLACK);
	root->left = rb_tree_node(root, 90, BLACK);
	root->right = rb_tree_node(root, 120, BLACK);
	root->left->left = rb_tree_node(root->left, 79, RED);
	root->left->right = rb_tree_node(root->left, 95, RED);
	root->right->left = rb_tree_node(root->right, 110, RED);
	root->right->right = rb_tree_node(root->right, 123, RED);
	return (root);
}

void rb_tree_print(const rb_tree_t *tree);

int main()
{
	rb_tree_t *root = valid_rb();
	/* rb_tree_print(root); */

	/* rb_tree_remove(root, 98); */
	/* rb_tree_print(root); */

	/* root = valid_rb(); */
	/* rb_tree_remove(root, 90); */
	/* rb_tree_print(root); */

	root = rb_tree_node(NULL, 23, BLACK);
	rb_tree_print(root);
	root = rb_tree_remove(root, 23);
	printf("%p\n", root);
	rb_tree_print(root);

	rb_tree_t *tree;
	int array[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	};
	size_t n = sizeof(array) / sizeof(array[0]);
	int rm_val = 68;

	tree = array_to_rb_tree(array, n);
	if (!tree)
		return (1);
	puts("Initial tree");
	rb_tree_print(tree);
	tree = rb_tree_remove(tree, rm_val);
	printf("After removing %i\n", rm_val);
	rb_tree_print(tree);

	return 0;
}
