
/*
* Vinh Nguyen #470821
*/

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

/**
 * Create a new instance of a binary search tree
 */
BST create_bst() {
	BST tree;
	tree.root = NULL;
	return tree;
}

/**
 * Locate specific node in a binary search tree
 * @param self
 * @param n value of node to locate
 * @return
 */
BSTNodePtr find_bst_node(BSTNodePtr self, long n) {

	if (self == NULL || n == self->id) {
		return self;
	}

	if (n < self->id) {
		return find_bst_node(self->left, n);
	}
	return find_bst_node(self->right, n);
}

/**
 * Locate specific node in a binary search tree
 * @param self
 * @param n value of node to locate
 * @return
 */
BSTNodePtr find_bst(BST *self, long n) {
	return find_bst_node(self->root, n);
}


/**
 * Insert a new node into a binary search tree
 * @param self tree
 * @param n value to insert
 * @return modified tree
 */
 /**
  * Insert a new node into a binary search tree and retur a new tree
  */
BSTNodePtr insert_bst_node(BSTNodePtr self, long n) {
	/* check if found correct the location, then insert */
	if (self == NULL) {
		self = malloc(sizeof *self);
		self->id = n;
		self->left = self->right = NULL;

	}
	else if (n < self->id) {
		self->left = insert_bst_node(self->left, n);
	}
	else if (n > self->id) {
		self->right = insert_bst_node(self->right, n);
	}

	return self;
}

/**
 * Insert a value in a binary search tree
 */
void insert_bst(BST *self, long n) {
	self->root = insert_bst_node(self->root, n);
}



/**
 * Find the minimum node in a given branch
 * @param self
 * @return
 */
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	// while there is a left branch
	while (current->left != NULL) {
		// move down the branch
		current = current->left;
	}
	return current;
}


/**
 * Remove a node from a binary search tree and return modified tree
 */
BSTNodePtr delete_bst_node(BSTNodePtr self, long n) {
	if (self != NULL) {
		if (self->id == n) {
			if (self->left != NULL && self->right != NULL) {
				BSTNodePtr successor = min_node(self->right);
				self->id = successor->id;
				self->right = delete_bst_node(self->right, self->id);

			}
			else {
				BSTNodePtr to_free = self;
				self = self->left ? self->left : self->right;
				free(to_free);
			}
		}
		else if (n < self->id) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	}
	return self;
}

/**
 * Remove a value from a binary search tree
 */
void delete_bst(BST *self, long n) {
	self->root = delete_bst_node(self->root, n);
}


/**
 * Clean all memory used by a binary search tree node
 * @param self tree node
 */
void destroy_bst_node(BSTNodePtr self) {

	if (self != NULL) {
		/* recursively destroy children */
		destroy_bst_node(self->left);
		destroy_bst_node(self->right);

		free(self);
	}
}

/**
 * Clean all memory used by a binary search tree
 * @param self tree
 */
void destroy_bst(BST *self) {
	destroy_bst_node(self->root);
}

/**
* print a binary search tree using in-order format
*/
void print_order_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		print_order_bst_node(self->left);
		printf("%d\n", self->id);
		print_order_bst_node(self->right);
	}
	
}

void print_in_order_bst(BST *self) {
	print_order_bst_node(self->root);
}


/**
* count the number of nodes inside the binary search tree
* this is useful for summerizing how many students are enrolled in a course.
* @param: self
* return: count
*/
int count_number_of_element_in_bst(BSTNodePtr self) {
	int count;
	if (self == NULL) {
		return 0;
	}
	count = 1 + count_number_of_element_in_bst(self->left) +
		count_number_of_element_in_bst(self->right);

		return count;
}

int number_of_element_int_bst(BST *self) {
	return count_number_of_element_in_bst(self->root);
}
