/* Created by Ilan Rosen 834282
for assignment 1, comp 20007, semester 1*/

#include <stdio.h>
#include "traverse.h"
#include "queue.h"
#include "stack.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void all_recurse(Graph* graph, int source, int dest, int *visited, Stack *path);
void shortest_recurse(Graph* graph, int source, int dest, int *visited, Stack *path, Stack *shortest_path, int curr_dist);
void detailed_recurse(Graph* graph, int source, int dest, int *visited, Stack *path, int* found, int curr_dist);
//Function which prints the Depth First Search result of the graph
void print_dfs(Graph* graph, int source_id) 
{
	//initializes an array of ints denoting if a node has been visited, the index of the int
	//is the source_id of the node, and an int keeping track of the previously visited node
	int *visited, prev;
	visited = calloc((graph->maxn), sizeof(int));
	assert(visited);
	//creating the stack which keeps track of the current path
	Stack* path = new_stack();
	//populates visited, prev, and the path with starting values
	stack_push(path, source_id);
	visited[source_id] = 1;
	prev = source_id;
	//creates a pointer to the first edge of the source node
	Edge* curr_edge = graph->vertices[source_id]->first_edge;
	while (stack_size(path) != graph->maxn)
	{
		//if the current node isnt visited, push it to the stack, make its int value 1 in visited
		//change the current edge to be the first edge of this new node and make prev the previous sourceid
		if (!visited[curr_edge->v])
		{
			prev = curr_edge->u;
			visited[curr_edge->v] = 1;
			stack_push(path, curr_edge->v);
			curr_edge = graph->vertices[curr_edge->v]->first_edge;
		}
		//else look at the next edge of the current node, if its null then look at the first edge of the
		//previous node
		else
		{
			curr_edge = curr_edge->next_edge;
			if (curr_edge == NULL)
			{
				curr_edge = graph->vertices[prev]->first_edge;
				prev = curr_edge->u;
			}
		}
	}
	//after the stack is full, print it to 
	print_stack(path,graph);
	free(visited);
	free_stack(path);
}

//function to print the breadth first search result of the given graph
void print_bfs(Graph* graph, int source_id) {
	//initializes an array of ints denoting if a node has been visited, the index of the int
	//is the source_id of the node, and an int keeping track of the current node we're looking at
	int *visited, curr_node;
	visited = calloc((graph->maxn), sizeof(int));
	assert(visited);
	//initializes the queue which will keep track of the crrent path traversed
	Queue *path;
	path = new_queue();
	//adds initial values to the path and the visited array 
	queue_enqueue(path, source_id);
	curr_node = source_id;
	visited[source_id] = 1;
	//initalzes curr_edge to be a pointer to the first edge of the source node
	Edge *curr_edge = graph->vertices[source_id]->first_edge;
	while (queue_size(path) != graph->maxn)
	{
		//if the current edge is null, set curr_edge to be the first edge of the current node we're looking at
		if (curr_edge == NULL)
		{
			curr_node = next_item_queue(path, curr_node);
			curr_edge = graph->vertices[curr_node]->first_edge;
		}
		else
		{
			//if the node hasnt been visited, add it to the queue
			//set visited to 1
			if (!visited[curr_edge->v])
			{
				visited[curr_edge->v] = 1;
				queue_enqueue(path, curr_edge->v);
			}
			//sets curr_edge to the next edge of the current node
			curr_edge = curr_edge->next_edge;
		}
	}
	//once the queue is full, print the queue
	print_queue(path, graph);
	free_queue(path);
	free(visited);
}

//function to print a path between the source id and the destination id, using BFS
//essentially an implementation of BFS which breaks when the destination is reached
void detailed_path(Graph* graph, int source_id, int destination_id) {
	//initializes an array of ints denoting if a node has been visited, the index of the int
	//is the source_id of the node, and an int keeping track of the current node we're looking at
	int *visited, found = 0;
	visited = calloc((graph->maxn), sizeof(int));
	assert(visited);
	Stack *path = new_stack();
	//creating the queue which keeps track of the current path
	stack_push(path, source_id);
	visited[source_id] = 1;
	printf("%s (%dkm)\n", graph->vertices[source_id]->label, 0);
	detailed_recurse(graph, source_id, destination_id, visited, path, &found, 0);
	free(visited);
	free_stack(path);
}


void detailed_recurse(Graph* graph, int source, int dest, int *visited, Stack *path, int* found, int curr_dist)
{
	if (*found)
		return;
	//sets the current edge to be the first edge of the node we're looking at
	Edge* curr_edge = graph->vertices[source]->first_edge;
	//same logic as DFS, if the node hasnt been explored, add it to the stack and then call 
	//the recursive function on that new node
	while (curr_edge)
	{
		if (*found)
			break;
		if (!visited[curr_edge->v])
		{
			curr_dist += curr_edge->weight;
			printf("%s (%dkm)\n", graph->vertices[curr_edge->v]->label, curr_dist);
			visited[curr_edge->v] = 1;
			stack_push(path, curr_edge->v);
			if (curr_edge->v == dest)
			{
				*found = 1;
				return;
			}
			else
			{
				detailed_recurse(graph, curr_edge->v, dest, visited, path, found,curr_dist);
			}
		}
		curr_edge = curr_edge->next_edge;
	}
	//resets the visited array and pops the node from the stack, as we've searched all its children
	//as per the recursive call
	visited[source] = 0;
	stack_pop(path);

}


//a function which prints all the paths between two nodes
void all_paths(Graph* graph, int source_id, int destination_id) {
	//creates the array of which towns have been visited, setting all values to 0
	int *visited;
	visited = calloc((graph->maxn), sizeof(int));
	assert(visited);
	//creates the stack for holding the current path traversed
	Stack* path = new_stack();
	//initializes the stack and visited
	stack_push(path, source_id);
	visited[source_id] = 1;
	//first call of recursive function to find all paths
	all_recurse(graph, source_id, destination_id, visited, path);
	free(visited);
	free_stack(path);
	
}

//recursive function called on a node, which explores all nodes surrounding it
//if theyve been visited, it ignores them, if the node hasnt been visited but is
//not the destination, it calls the function again on that node
//otherwise, it prints out the current queue, as it's reached its dest
//after the all the nodes surrounding the current node have been visited, it resets 
//visited so the current node isn't visited anymore
void all_recurse(Graph* graph, int source, int dest, int *visited, Stack *path)
{
	//sets the current edge to be the first edge of the node we're looking at
	Edge* curr_edge = graph->vertices[source]->first_edge;
	//same logic as DFS, if the node hasnt been explored, add it to the stack and then call 
	//the recursive function on that new node
	while (curr_edge)
	{
		if (!visited[curr_edge->v])
		{
			visited[curr_edge->v] = 1;
			stack_push(path, curr_edge->v);
			if (curr_edge->v == dest)
			{
				print_stack_all(path, graph);
				printf("\n");
				visited[curr_edge->v] = 0;
				stack_pop(path);
			}
			else
			{
				all_recurse(graph, curr_edge->v, dest, visited, path);
			}
		}
		curr_edge = curr_edge->next_edge;
	}
	//resets the visited array and pops the node from the stack, as we've searched all its children
	//as per the recursive call
	visited[source] = 0;
	stack_pop(path);

}

//same as searching for all the paths, except the distance of the current path
//is also tracked as its an element of the stack
//if the destination is reached and its distance is shorter, or its the first time the destination
//has been reached, it copies the current stack into the shortest_path stacks
void shortest_path(Graph* graph, int source_id, int destination_id) {

	int *visited;
	visited = calloc((graph->maxn), sizeof(int));
	assert(visited);
	Stack *path = new_stack(), *shortest_path = new_stack();
	stack_push(path, source_id);
	visited[source_id] = 1;
	shortest_recurse(graph, source_id, destination_id, visited, path, shortest_path, 0);
	print_stack_all(shortest_path, graph);
	printf(" (%dkm)\n", get_stack_dist(shortest_path));
	free(visited);
	free_stack(path);

}
//same as finding all paths, except an extra check has been added at position --1--
void shortest_recurse(Graph* graph, int source, int dest, int *visited, Stack *path, Stack *shortest_path, int curr_dist)
{
	Edge* curr_edge = graph->vertices[source]->first_edge;
	while (curr_edge)
	{
		if (!visited[curr_edge->v])
		{
			visited[curr_edge->v] = 1;
			stack_push(path, curr_edge->v);
			if (curr_edge->v == dest)
			{
				//--1--: if the destination has been reached and the current distance is shorter than the
				//previous path held in the shortest path stack, or its the first time
				//reaching the destination, copy the current path into the shortest path
				if (curr_dist + curr_edge->weight < get_stack_dist(shortest_path) || !get_stack_dist(shortest_path))
				{
					copy_stack(path, shortest_path);
					set_stack_dist(shortest_path, curr_dist + curr_edge->weight);
				}
				visited[curr_edge->v] = 0;
				stack_pop(path);
			}
			else
			{
				shortest_recurse(graph, curr_edge->v, dest, visited, path, shortest_path, curr_dist + curr_edge->weight);
			}
		}
		curr_edge = curr_edge->next_edge;
	}
	visited[source] = 0;
	stack_pop(path);

}



