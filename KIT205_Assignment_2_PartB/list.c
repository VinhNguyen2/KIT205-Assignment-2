/*
* Vinh Nguyen #470821
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"


/*
 Create a new instance of the list type
*/
CourseList new_list() {
	CourseList self;
	self.head = NULL;
	return self;
}


/*
 Insert a new node in an ordered list
*/

void insert_in_order(CourseList *self, String data) {
	CourseNodePtr current = self->head;
	CourseNodePtr prev = NULL;

	CourseNodePtr new_node = malloc(sizeof *new_node);
	new_node->course = malloc((strlen(data) + 1) * sizeof(String));

	strcpy(new_node->course, data);

	new_node->students.root = NULL;

	new_node->next = NULL;

	while (current != NULL && strcmp(current->course, data) < 0) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // inserting at the front
		new_node->next = current;
		self->head = new_node;
	}
	else {
		new_node->next = current;
		prev->next = new_node;
	}
}


/**
*Traverse the link-list to find the 'target' course.
*/
CourseNodePtr search_linkedlist(CourseList *self, String target) {
	CourseNodePtr current = self->head;
	while (current != NULL)
	{
		if (strcmp(current->course, target) == 0)
		{
			return current;
		}
		else
		{
			current = current->next;
		}
	}
	return NULL;
}


/**
* Delete an item from a list
*/
void delete_list(CourseList *self, String target) {
	CourseNodePtr current = self->head;
	CourseNodePtr prev = NULL;

	while (current != NULL) {

		if (strcmp(current->course, target) == 0) {
			/*Check if the node is the first element in the linked-list*/
			if (prev == NULL) {
				self->head = current->next;

				destroy_avl(&current->students);
				free(current->course);
				current->course = NULL;

				free(current);
				current = self->head;
			}
			/*remove target from n'th position*/
			else {
				prev->next = current->next;

				destroy_avl(&current->students);
				free(current->course);
				current->course = NULL;
				free(current);

				current = prev->next;
			}
		}
		/*Target node not yet fround, traverse, upeating current and previous*/
		else {
			prev = current;
			current = current->next;
		}
	}
}

/**
 * Remove an entire list: distroy all courselist nodes
 * and AVL tree of students.
 * @param self
 */
void destroy_list(CourseList *self) {
	CourseNodePtr current = self->head;
	while (current != NULL) {
		CourseNodePtr to_free = current;
		current = current->next;

		destroy_avl(&to_free->students);
		free(to_free->course);
		free(to_free);
	}
	self->head = NULL;
}

