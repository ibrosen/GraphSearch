/* * * * * * *
* Module for creating and manipulating stacks of integers
*
* created for COMP20007 Design of Algorithms 2017
* by Matt Farrugia <matt.farrugia@unimelb.edu.au>
edited by Ilan Rosen to add print stack function
*/

// 'include guards': these lines (and #endif at the bottom) prevent this file
// from being included multiple times. multiple inclusion can cause errors on
// some compilers, especially if the included file contains struct definitions
// how it works: https://en.wikipedia.org/wiki/Include_guard
#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;


// create a new stack and return its pointer
Stack *new_stack();

// destroy a stack and its associated memory
void free_stack(Stack *stack);

//returns the current distance stored in stack
int get_stack_dist(Stack *stack);

//adds to the current stack distance
void add_stack_dist(Stack *stack, int path_dist);

//sets current distance stored in stack
void set_stack_dist(Stack *stack, int val);

//copies contents of one stack to another
void copy_stack(Stack *source, Stack *dest);

//minuses from current stack distance
void minus_stack_dist(Stack *stack, int path_dist);

//prints items in a stack, as defined by string labels in graph
void print_stack(Stack *stack, Graph *graph);

//same as print_stack, except different format specific to Q4
void print_stack_all(Stack *stack, Graph *graph);

// push a new item of data onto the top of a stack. O(1).
void stack_push(Stack *stack, int data);

// remove and return the top item of data from a stack. O(1).
// error if the stack is empty (so first ensure stack_size() > 0)
int stack_pop(Stack *stack);

// return the number of items currently in a stack
int stack_size(Stack *stack);

#endif