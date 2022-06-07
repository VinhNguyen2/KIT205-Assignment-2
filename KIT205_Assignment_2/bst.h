#pragma once

/*
* Vinh Nguyen #470821
*/


/**
 * Data type for a node in a binary search tree
 */
typedef struct bstNode {
	long id;
	struct bstNode *left;
	struct bstNode *right;
} *BSTNodePtr;

/**
 * Wrapper type for a binary search tree
 */
typedef struct bst {
	BSTNodePtr root;
} BST;

/**
 * Create a new instance of a binary search tree
 */
BST create_bst();

/**
 *Find specific node in a binary search tree
 */
BSTNodePtr find_bst(BST *self, long n);

/**
 * Insert a new node into a binary search tree and return a new tree
 */
void insert_bst(BST *self, long n);


/**
 * Remove a value from a binary search tree
 * @param self tree
 * @param n value to remove
 */
void delete_bst(BST *self, long n);

/**
 * Clean all memory used by a binary search tree
 * @param self tree
 */
void destroy_bst(BST *self);

/**
 * Print a binary search tree using in-order format
 */
void print_in_order_bst(BST *tree);


/**
* Count the number of nodes inside the binary search tree
* this is useful for summerizing how many students are enrolled in a course.
* @param: self
* @return: count
*/
int number_of_element_int_bst(BST *self);





