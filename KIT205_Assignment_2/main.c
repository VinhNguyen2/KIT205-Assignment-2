/*
* Vinh Nguyen #470821
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "list.h"
#include "bst.h"

#define MIN_CHOISE 0
#define MAX_CHOISE 7



/**
* promp to enter a student ID number
* @return capture input
*/
long prompt_student_id() {
	long student_id;
	printf("Enter student id:\n ");
	scanf("%ld", &student_id);
	return student_id;
}

/**
* prompt to enter a course name
* @return cuptured input
*/
char *prompt_course_name() {
	char buffer[100];

	printf("Enter course: \n");
	scanf("%s", buffer);

	String course_name = malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(course_name, buffer);

	return course_name;
}

/**
* Add a course to the records 
* @param self
*/
void add_course(CourseList *self) {
	String course_name = prompt_course_name();

	insert_in_order(self, course_name);
}

/**
* Remove a course from the records 
*/
void remove_course(CourseList *self) {
	String course_name = prompt_course_name();

	delete_list(self, course_name);
}

/**
* Enroll student in a course
* @param self
*/
void enroll_student(CourseList *self) {
	String course_name = prompt_course_name();
	long student_id = prompt_student_id();

	/*Finds the course to add the student to .*/
	CourseNodePtr temp = search_linkedlist(self, course_name);

	/* once the CourseList node has been found, add sutdent_id to it's BST*/
	 insert_bst(&temp->students, student_id);
}

/**
* Unenroll student from a couse
* @param self
*/

void unenroll_student(CourseList *self) {
	String course_name = prompt_course_name();
	long student_id = prompt_student_id();

	/*Finds the course to delete the student in that course .*/
	CourseNodePtr temp = search_linkedlist(self, course_name);
	
	/* once the CourseList node has been found, delete the sutdent_id in BST*/
	delete_bst(&temp->students, student_id);
}

/**
* This function finds the course with the name as the target.
* then traverses through the target's BST tree of students.
* @param: self
*/

void print_course_enrolled(CourseList *self) {
	String course_name = prompt_course_name();

	/*Finds the course */
	CourseNodePtr temp = search_linkedlist(self, course_name);

	/* Print a binary search tree using in - order format */ 
	print_in_order_bst(&temp->students);

}

/**
* Display all the course names (from the linked list) and counts
* the number of nodes inside the BST representing students.
*@param: self
*/

void print_sourse_summary(CourseList *self) {
	int number_of_students;
	CourseNodePtr current = self->head;

	while (current !=NULL)
	{
		number_of_students = number_of_element_int_bst(&current->students);
		printf("%s %d\n", current->course, number_of_students);
		current = current->next; 
	}
}

/**
* Search all the CourseList node's BST trees for all occurences of 
* the targer student's id and displays the course names where found.
* @param: self
*/

void print_student_enrolled_courses(CourseList *self) {
	long student_id = prompt_student_id();

	CourseNodePtr current = self->head;
	while (current != NULL)
	{
		if (find_bst(&current->students, student_id))
		{
			printf("%s\n", current->course);
		}
		current = current->next;
	}
}

/*Possible oporations that the program can do. Used in conjuction with switch*/
enum
{
	ADD_COURSE = 1,
	REMOVE_COURSE = 2,
	ENROL_STUDENT = 3,
	UN_ENROL_STUDENT =4,
	COURSE_SUMMARY = 5,
	STUDENT_ENROL_IN_COURSE =6,
	LIST_OF_COURSE_A_STUDENT_ENRROLED
};

void display_options() {

	printf("\n");
	printf("Please pick an option(1-7). if you want to to exit pick 0.\n");
	printf("1. Add course\n");
	printf("2. Remove course\n");
	printf("3. Enrole student\n");
	printf("4. Un-enrole student\n");
	printf("5. Print an ordered summary of courses and the number\n   of students enrolled in each course\n");
	printf("6. Print an ordered list of students enrolled in a course\n");
	printf("7. Print an ordered list of courses that a given student is enrolled in\n");
	printf("===================================\n");
	printf("Enter your option:\n");

}

void selected_task(CourseList *self, int user_choice) {
	switch (user_choice) {
	case ADD_COURSE:
		add_course(self);
		break;

	case REMOVE_COURSE:
		remove_course(self);
		break;

	case ENROL_STUDENT:
		enroll_student(self);
		break;

	case UN_ENROL_STUDENT:
		unenroll_student(self);
		break;

	case COURSE_SUMMARY:
		print_sourse_summary(self);
		break;

	case STUDENT_ENROL_IN_COURSE:
		print_course_enrolled(self);
		break;

	case LIST_OF_COURSE_A_STUDENT_ENRROLED:
		print_student_enrolled_courses(self);
		break;
	}
}

int choice()
{
	int option_choise;

	do {
		scanf("%d", &option_choise);
	} while (option_choise < MIN_CHOISE || option_choise > MAX_CHOISE);
	return option_choise;
}

int main() {
	CourseList courses = new_list();

	/* Asssigned by choise(). Stores a value between 0-7 sellected by user. */
	unsigned short user_choise;

	do {
		display_options();
		user_choise = choice();
		selected_task(&courses, user_choise);
	} while (user_choise != 0);
	if (courses.head != NULL) {
		
	/*Destroy all courselist node an the BST tree of students*/
		destroy_list(&courses);
	}

	return 0;
}








