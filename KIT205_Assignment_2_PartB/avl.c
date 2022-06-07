/*
* Vinh Nguyen #470821
*/


#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

/**
 * Create a new instance of an AVL tree
 */
AVL create_avl() {
	AVL tree;
	tree.root = NULL;
	return tree;
}


/**
* Maximum: takes two int value and returns the largest of the two
* @param a, b
* return a or b
*/
int maximum(int a, int b) {
	return(a > b) ? a : b;
}

/**
* Get the hight of the node
* @return int
*/
int height(AVLNodePtr self) {
	int left_height = 0;
	int right_height = 0;

	if (self == NULL) {
		return left_height > right_height ? left_height : right_height;
	}

	left_height = height(self->left);
	right_height = height(self->right);
}



/**
* Check balance: this function conts the height of the left and right subtrees
* and checks if they are balanced
@param self
* return: 0 if both branches are equal, otherwise a negative value if left
* branch is heigher or a positive value if the right side is heigher
*/

int check_balance(AVLNodePtr self) {
	if (self == NULL) {
		return 0;
	}
	return height(self->left) - height(self->right);
}



/**
* Rotates an unbalanced node to the right
* @param self
* return the balance tree
*/
AVLNodePtr right_rotate(AVLNodePtr parent) {
	AVLNodePtr temp = parent;
	AVLNodePtr child = parent->left;
	AVLNodePtr grandchild = child->left;

	/* swap nodes*/
	parent = child;
	temp->left = parent->right;
	parent->right = temp;

	/*update height of AVL tree*/
	parent->height = maximum(height(parent->left), height(parent->right)) + 1;

	return child;
}


/**
* Rotates an unbalanced node to the left
* @param self
* return the balance tree
*/

AVLNodePtr left_rotate(AVLNodePtr parent) {
	AVLNodePtr temp = parent;
	AVLNodePtr child = parent->right;
	AVLNodePtr grandchild = child->right;

	/* swap nodes*/
	parent = child;
	temp->right = parent->left;
	parent->left = temp;

	/*update height of AVL tree*/
	parent->height = maximum(height(parent->left), height(parent->right)) + 1;

	return child;
}


/**
* rebalance avl: Checks if the left and right branches of the tree are even,
* if they are not. Check which rotation needs to be carried out and do it.
* @param self
* Return: a newly balanced tree if rebalancing is needed, or just returns 
* the current root if no balancing is necessary.
*/

AVLNodePtr rebalance_avl(AVLNodePtr self, int n) {
	int balance;

	/*update the height of the ancestor*/
	self->height = maximum(height(self->left), height(self->right))+1;

	/*check that the left and right subtrees are banaced*/
	balance = check_balance(self);

	/*check for left rotate*/
	if (balance > 1 && n < self ->id) {
		return right_rotate(self);
	}

	/*check for right rotate*/
	if (balance < -1 && n > self->id) {
		return left_rotate(self);
	}

	/*check for double rotate (left then right)*/
	if (balance > 1 && n > self->left->id) {
		self->left = left_rotate(self);
		return right_rotate(self);
	}

	/*check for double rotate (right then left)*/
	if (balance < -1 && n < self->right->id) {
		self->right = right_rotate(self);
		return left_rotate(self);
	}
	return self;
}

/**
 * Insert a new node into an AVL tree
 * @param self tree
 * @param n value to insert
 * @return modified tree
 */
 /**
  * Insert a new node into a avl tree and return a new tree
  */
AVLNodePtr insert_avl_node(AVLNodePtr self, long n) {
	/* check if found correct the location, then insert */
	if (self == NULL) {
		self = malloc(sizeof *self);
		self->id = n;
		self->height = 1;
		self->left = self->right = NULL;

	}
	else if (n < self->id) {
		self->left = insert_avl_node(self->left, n);
	}
	else if (n > self->id) {
		self->right = insert_avl_node(self->right, n);
	}

	self = rebalance_avl(self, n);

	return self;
}


/**
 * Insert a value in a AVL tree
 */
void insert_avl(AVL *self, long n) {
	self->root = insert_avl_node(self->root, n);
}


/**
 * Locate specific node in a AVL tree
 * @param self
 * @param n value of node to locate
 * @return
 */
AVLNodePtr find_avl_node(AVLNodePtr self, long n) {

	if (self == NULL || n == self->id) {
		return self;
	}

	if (n < self->id) {
		return find_avl_node(self->left, n);
	}
	return find_avl_node(self->right, n);
}

/**
 * Locate specific node in an AVL tree
 * @param self
 * @param n value of node to locate
 * @return
 */
AVLNodePtr find_avl(AVL *self, long n) {
	return find_avl_node(self->root, n);
}


/**
 * Find the minimum node in a given branch
 * @param self
 * @return
 */
AVLNodePtr min_node(AVLNodePtr self) {
	AVLNodePtr current = self;
	// while there is a left branch
	while (current->left != NULL) {
		// move down the branch
		current = current->left;
	}
	return current;
}


/**
 * Remove a node from an AVL tree and return modified tree
 */
AVLNodePtr delete_avl_node(AVLNodePtr self, long n) {
	if (self != NULL) {
		if (self->id == n) {
			if (self->left != NULL && self->right != NULL) {
				AVLNodePtr successor = min_node(self->right);
				self->id = successor->id;
				self->right = delete_avl_node(self->right, self->id);

			}
			else {
				AVLNodePtr to_free = self;
				self = self->left ? self->left : self->right;
				free(to_free);
			}
		}
		else if (n < self->id) {
			self->left = delete_avl_node(self->left, n);
		}
		else {
			self->right = delete_avl_node(self->right, n);
		}
	}
	return self;
}

/**
 * Remove a value from an AVL tree
 */
void delete_avl(AVL *self, long n) {
	self->root = delete_avl_node(self->root, n);
}


/**
* print an AVL tree using in-order format
*/
void print_order_avl_node(AVLNodePtr self) {
	if (self != NULL) {
		print_order_avl_node(self->left);
		printf("%d\n", self->id);
		print_order_avl_node(self->right);
	}
	
}

/**
* print an AVL tree using in-order format
*/
void print_in_order_avl(AVL *self) {
	print_order_avl_node(self->root);
}


/**
* count the number of nodes inside the AVL tree
* this is useful for summerizing how many students are enrolled in a course.
* @param: self
* return: count
*/
int count_number_of_element_in_avl(AVLNodePtr self) {
	int count;
	if (self == NULL) {
		return 0;
	}
	count = 1 + count_number_of_element_in_avl(self->left) +
		count_number_of_element_in_avl(self->right);

		return count;
}

int number_of_element_int_avl(AVL *self) {
	return count_number_of_element_in_avl(self->root);
}

/**
 * Clean all memory used by an AVL tree node
 * @param self tree node
 */
void destroy_avl_node(AVLNodePtr self) {

	if (self != NULL) {
		/* recursively destroy children */
		destroy_avl_node(self->left);
		destroy_avl_node(self->right);

		free(self);
	}
}

/**
 * Clean all memory used by an AVL tree
 * @param self tree
 */
void destroy_avl(AVL *self) {
	destroy_avl_node(self->root);
}