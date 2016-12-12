/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #5

 File: graph.h

 Purpose: This file is the core of the Graph ADT and the class "graph" created in this file acts as the manager of
 the data structure used in the project (Adjacency List). This class handles the initialization of the graph
 (constructor), setting the data for individual nodes (add_vertex), retrieving data based on a vertex's edge list
 (retrieve_adj, retrieve_graph), and displaying data using a depth-first traversal approach (display, display_graph).

 The private section of the "graph" class contains an external pointer and a index variable used to by the Adjacency List.
 In addition, all the recursive function definitions associated with certain pulic ADT operations are defined in the section.
 Also, a copy function used to deep-copy the data out of a vertex_info object into the Adjacency List or 'results' array, is
 defined in the section as well.

 The public functions (retrieve_adj and display) act as 'wrappers' which utilize private recursive functions to carry out
 direct operations on the Adjacency List. This is done in order to keep the access to complex data structure operations limited
 to the class and not provide direct access to the client side of the program. */

#ifndef GRAPH_H
#define GRAPH_H

#include "vertex_node.h"
#include "vertex_info.h"

const int GRAPH_SIZE = 30; //Sets the size of the Adjacency List

class graph
{
public:
    //Constructor
	graph();

	//Destructor
	~graph();

	int add_vertex(vertex_info& a_vertex); //Adds vertex information to the Adjacency List
    int add_edge(const char topic[], const char dependency[]); //Adds a node to a vertex's edge list
    int search(const char search_topic[]); //Searches the adjacency list looking for a vertex that matches the passed in search topic.
    int retrieve_adj(const char topic[], vertex_info results[]); //Returns topics that are adjacent to a particular vertex back to main via 'results' array.
    int display(const char topic[]);//Displays topics using a depth-first traversal with a starting position that is set by the user.



private:

    //Recursive function which copies topics into an object array that are adjacent to a particular vertex.
    void retrieve_graph(edge_node * current, vertex_info results[], int& count);

    //Recursive function that displays infromation using a depth-first traversal.
    void display_graph(vertex_node& start , edge_node * current);

    //Copies data from one vertex_info object to another
    void copy(vertex_info &to_vertex, vertex_info& from_vertex);

    vertex_node * adj_list;
    int index;


};
#endif
