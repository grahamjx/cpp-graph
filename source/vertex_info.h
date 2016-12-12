/*
 Name: Joel Graham
 Course: CS 163
 Programming Assignment #5

 File: vertex_info.h

 Purpose: This file declares the struct "vertex_info". This struct holds the data that is used by the graph class.
 Each variable for a given instance of the struct (a_vertex) is set to the information entered by the user in main.
 When the object is passed from main into the graph class function "add_vertex", the information is copied into the
 the corresponding node. Inserting items into the adjacency list occurs in sequential order starting at element zero
 and continuing until it has reach the end of the array. When data is copied, the graph class private function "copy"
 is called which handles the deep copy of the information from the passed in object (a_vertex) to whatever node requires
 the information (adj_list[index].data). See "copy" function in graph.cpp for more clarification. */

#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

struct vertex_info
{
    char * topic;
};

#endif
