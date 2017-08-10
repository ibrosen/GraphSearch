/* * * * * * *
* Module for creating and manipulating singly-linked lists of integers
*
* created for COMP20007 Design of Algorithms 2017
* by Matt Farrugia <matt.farrugia@unimelb.edu.au>
Edited by Ilan Rosen 834282
*/

// 'include guards': these lines (and #endif at the bottom) prevent this file
// from being included multiple times. multiple inclusion can cause errors on
// some compilers, especially if the included file contains struct definitions
// how it works: https://en.wikipedia.org/wiki/Include_guard
#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "graph.h"
typedef struct list List;

// create a new list and return its pointer
List *new_list();

// destroy a list and free its memory
void free_list(List *list);

//prints out the items in a queue's list as defined by their labels in a graph, 
void print_queue_list(List *list, Graph* graph);

//same as print_stack_list, except different format
void print_stack_list_all(List *list, Graph *graph);

//copies content from one list to another
void copy_list(List *source, List *dest);

//prints all the items in the list inside a stack, as per print_list_graph
void print_stack_list(List *list, Graph* graph);

//function to return the next item in the list
int next_item_list(List* list, int val);

// add an element to the front of a list
// this operation is O(1)
void list_add_start(List *list, int data);

// add an element to the back of a list
// this operation is O(1)
void list_add_end(List *list, int data);

// remove and return the front data element from a list
// this operation is O(1)
// error if the list is empty (so first ensure list_size() > 0)
int list_remove_start(List *list);

// remove and return the final data element in a list
// this operation is O(n), where n is the number of elements in the list
// error if the list is empty (so first ensure list_size() > 0)
int list_remove_end(List *list);

// return the number of elements contained in a list
int list_size(List *list);

// returns whether the list contains no elements (true) or some elements (false)
bool list_is_empty(List *list);

#endif
