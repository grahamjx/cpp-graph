/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #5

 File: edge_node.h

 Purpose: This file declares the struct "edge_node". This struct is used to build each node in the edge list associated with a
 particular vertex. Each node is comprised of an integer variable 'vertex' as well as a next pointer. The vertex variable is used
 to store the index value where a particular vertex resides in the adjacency list. The next pointer is used to point to the next node
 in the edge list (LLL). This struct is utilized when the user decides to set a dependency using the main function 'add_depend'. If
 the dependency that the user wants to associate with a topic exists as a vertex, then the index value (position) for that
 vertex is saved to the edge node's vertex variable. */

#ifndef EDGE_NODE_H
#define EDGE_NODE_H

struct edge_node
{
    int vertex;
    edge_node * next;
};

#endif
