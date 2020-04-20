#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

/**
 * valid_rb - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *valid_rb(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);
    root->left = rb_tree_node(root, 90, BLACK);
    root->right = rb_tree_node(root, 120, BLACK);
    root->left->left = rb_tree_node(root->left, 79, RED);
    root->left->right = rb_tree_node(root->left, 95, RED);
    return (root);
}

/**
 * valid_rb - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *invalid_blk_h(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);
    root->left = rb_tree_node(root, 90, BLACK);
    root->right = rb_tree_node(root, 120, BLACK);
    root->right->left = rb_tree_node(root->right, 110, BLACK);
    root->left->left = rb_tree_node(root->left, 79, RED);
    root->left->right = rb_tree_node(root->left, 95, RED);
    return (root);
}

/**
 * valid_rb - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *not_valid_bst(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 98, BLACK);
	root->left = rb_tree_node(root, 90, BLACK);
	root->right = rb_tree_node(root, 120, BLACK);
	root->left->left = rb_tree_node(root->left, 79, RED);
	root->left->right = rb_tree_node(root->left, 95, RED);
	root->left->right->left = rb_tree_node(root->left->right, 96, RED);
	return (root);
}

/**
 * not_valid_rb - Builds a not valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *not_valid_rb(void)
{
    rb_tree_t *root;

    root = rb_tree_node(NULL, 98, BLACK);
    root->left = rb_tree_node(root, 90, RED);
    root->right = rb_tree_node(root, 120, RED);
    root->left->left = rb_tree_node(root->left, 79, BLACK);
    root->left->right = rb_tree_node(root->left, 95, BLACK);
    root->left->right->left = rb_tree_node(root->left->right, 92, RED);
    root->left->right->right = rb_tree_node(root->left->right, 96, RED);
    root->right->right = rb_tree_node(root->right, 130, BLACK);
    return (root);
}

/**
 * valid_rb - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *invalid_rb2(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 98, BLACK);
	root->left = rb_tree_node(root, 90, BLACK);
	root->left->left = rb_tree_node(root->left, 79, BLACK);
	return (root);
}

/**
 * main - Entry point
 *
 * Return: Always EXIT_SUCCESS
 */
int main(void)
{
    rb_tree_t *root;
    int valid;
    char *str = "\n**********************************************************************\n";

    printf("%s\n", str);

    root = valid_rb();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : true\n", root->n, valid);

    printf("%s\n", str);

    root = not_valid_rb();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : false\n", root->n, valid);

    printf("%s\n", str);

    root = not_valid_rb();
    root->right->left = rb_tree_node(root->right, 110, BLACK);
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : true\n", root->n, valid);

    printf("%s\n", str);

    root = not_valid_bst();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : false\n", root->n, valid);

    printf("%s\n", str);

    root->color = RED;
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d\n", root->n, valid);

    printf("%s\n", str);

    root = invalid_blk_h();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : false\n", root->n, valid);

    printf("%s\n", str);

    root = invalid_blk_h();
    root->right->left->color = RED;
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : true\n", root->n, valid);

    printf("%s\n", str);

    printf("%s\n", str);

    root = invalid_rb2();
    rb_tree_print(root);
    valid = rb_tree_is_valid(root);
    printf("Is %d valid: %d, EXP : false\n", root->n, valid);

    printf("%s\n", str);

    return (EXIT_SUCCESS);
}
