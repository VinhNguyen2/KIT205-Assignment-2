#pragma once

/*
* Vinh Nguyen #470821
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "bst.h"

typedef char *String;

typedef struct listNode {
	String course;
	BST students;
	struct listNode *next;
} *CourseNodePtr;

typedef struct list {
	CourseNodePtr head;
} CourseList;

/*
Create a new instance of the list type
*/
CourseList new_list();

/*
Insert a new element in an ordered list
*/
void insert_in_order(CourseList *self, String data);

/**
*Traverse the link-list to find the 'target' course.
*/
CourseNodePtr search_linkedlist(CourseList *self, String target);

/*
Delete an item from a list
*/
void delete_list(CourseList *self, String data);


/*
 Delete all items in a list
 */
void destroy_list(CourseList *self);


