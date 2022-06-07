#pragma once
/*
* Vinh Nguyen #470821
*/

/**
 * Data type for a node in an AVL tree
 */
typedef struct avlNode {
	long id;
	struct avlNode *left;
	struct avlNode *right;
	int height;
} *AVLNodePtr;

/**
 * Wrapper type for an AVL tree
 */
typedef struct bst {
	AVLNodePtr root;
} AVL;

/**
 * Create a new instance of an AVL tree
 */
AVL create_avl();

/**
 *Find specific node in an AVL tree
 */
AVLNodePtr find_avl(AVL *self, long n);

/**
 * Insert a new node into an AVL and return a new tree
 */
void insert_avl(AVL *self, long n);


/**
 * Remove a value from an AVL tree
 * @param self tree
 * @param n value to remove
 */
void delete_avl(AVL *self, long n);

/**
 * Clean all memory used by an AVL tree
 * @param self tree
 */
void destroy_avl(AVL *self);

/**
 * Print an AVL using in-order format
 */
void print_in_order_avl(AVL *tree);


/**
* Count the number of nodes inside an AVL tree
* this is useful for summerizing how many students are enrolled in a course.
* @param: self
* return: count
*/
int number_of_element_int_avl(AVL *self);





