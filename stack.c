/* * * * * * *
* Module for creating and manipulating stacks of integers
*
* created for COMP20007 Design of Algorithms 2017
* by Matt Farrugia <matt.farrugia@unimelb.edu.au>
edited by Ilan Rosen 834282
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"	// gives us access to everything defined in list.h
#include "stack.h"  // and we'll also need the prototypes defined in queue.h

// a stack is just a wrapper for a list of integers
// we will use the front of the list as the top of the stack (to take advantage
// of O(1) insert and remove operations)


struct stack {
	List *items;
	int dist;
};

/* * * *
* FUNCTION DEFINITIONS
*/

// create a new stack and return its pointer
Stack *new_stack() {
	Stack *stack = malloc(sizeof *stack);
	assert(stack);

	stack->items = new_list();
	//stack->dist = malloc(sizeof(int));
	stack->dist = 0;
	return stack;
}

//prints items in a stack, as defined by string labels in graph
void print_stack(Stack *stack, Graph* graph)
{
	print_stack_list(stack->items, graph);
}

//same as print_stack, except different format specific to Q4
void print_stack_all(Stack *stack, Graph *graph)
{
	print_stack_list_all(stack->items, graph);
}

//returns the current distance stored in stack
int get_stack_dist(Stack *stack)
{
	return stack->dist;
}

//sets current distance stored in stack
void set_stack_dist(Stack *stack, int val)
{
	//printf("------SET-----");;
	stack->dist = val;
	//printf("__%d__", *(stack->dist));
}

/*
//adds to the current stack distance
void add_stack_dist(Stack *stack, int path_dist)
{
	stack->dist += path_dist;
}


//minuses from current stack distance
void minus_stack_dist(Stack *stack, int path_dist)
{
	stack->dist -= path_dist;
}
*/
//copies one stack into another
void copy_stack(Stack *source, Stack *dest)
{
	copy_list(source->items, dest->items);
}

// destroy a stack and its associated memory
void free_stack(Stack *stack) {
	assert(stack != NULL);
	// free the list of items, and the stack itself
	free_list(stack->items);
	free(stack);
}

// push a new item of data onto the top of a stack. O(1).
void stack_push(Stack *stack, int data) {
	assert(stack != NULL);
	// the 'start' of the list will be our access point
	list_add_start(stack->items, data);
}

// remove and return the top item of data from a stack. O(1).
// error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop(Stack *stack) {
	assert(stack != NULL);
	assert(stack_size(stack) > 0);

	// the 'start' of the list will be our access point
	return list_remove_start(stack->items);
}

// return the number of items currently in a stack
int stack_size(Stack* stack) {
	assert(stack != NULL);
	// delegate straight to list size function
	return list_size(stack->items);
}