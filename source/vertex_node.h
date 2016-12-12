/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #5

 File: vertex_node.h

 Purpose: This file declares the struct "vertex_node". This struct is used to build each vertex node in the adjacency list.
 Each node is comprised of a "vertex_info" data object along with a edge_node head pointer and a flag variable. The edge_node
 pointer in each node points to the edge list (LLL) for a particular vertex. The flag variable is utilized when carrying out the
 depth-first traversal so that the vertex information that has already been accessed is not displayed again. The data for each object
 is set to the information passed in from main function "add_vertex". The external pointer "adj_list" which points to the adjacency
 list (array of vertex node's) is declared in graph.h. */

#ifndef VERTEX_NODE_H
#define VERTEX_NODE_H

#include "vertex_info.h"
#include "edge_node.h"

struct vertex_node
{
    vertex_info data;
    edge_node * head;
    bool flag;
};

#endif
