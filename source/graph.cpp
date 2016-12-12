/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #5

 File: graph.cpp

 Purpose: This file contains the function definitions for the class "graph" found in "graph.h".
 These functions are used to carry out proccess that deal with the Graph ADT and its corresponding
 data structure (adjacency list). Creating and destroying the graph, setting node data, searching
 / extracting data from nodes, and displaying node information are some of the operations carried
 out by this file.

 Input: This file utilizes input provided from the main function as well as from the "vertex_info"
 struct which supplies the data for each individual node.

 Output: Displays a limited amount of information found in each node out to the user. */

#include "graph.h"
#include <iostream>
#include <cstring> //Included to allow the use of strcpy, strlen in member functions. Also was required for Unix g++ compile.

using namespace std;

/* The function points the adj_list pointer in the private section to a new array of vertex nodes. The size of the array is
 determined by the constant found in graph.h. After the new array has been allocated and the index variable has been set to zero,
 each node in the adjacency list has its corresponding variables set to their initial value. */

graph::graph()
{
    index = 0;
    adj_list = new vertex_node[GRAPH_SIZE];

    for (int i = 0; i < (GRAPH_SIZE-1); i++)
    {
        adj_list[i].data.topic = '\0';
        adj_list[i].flag = false;
        adj_list[i].head = NULL;
    }
}

//Deletes the adjacency list
graph::~graph()
{
    delete [] adj_list;
}


/* This function takes in the vertex_info object "a_vertex" that contains the information entered by the user. The function
 first checks the index value to make sure it falls within the boundary of the array. The item is then copied into the
 adjacency list using the copy function. Vertex information is added incrementally, starting at position zero in the array. */

int graph::add_vertex(vertex_info& a_vertex)
{
    if (index >= (GRAPH_SIZE-1)) //Checks to make sure the index is within bounds
    {
        return 0;
    }
    else
    {
        copy(adj_list[index].data, a_vertex); //Copies the data from the passed in object into the correct node
        index++;
        return 1;
    }
}


/* This function takes in a two character arrays from main. The first one, 'topic', represents the
 topic that the user would like to associate a dependency with. The second one, 'dependency', represents
 which topic the dependency should be. First, the 'topic' is passed to the class function "search" which
 searches through the vertex nodes in the adjacency list looking for a matching topic. The search function will
 either return a -1 back to the calling function if the item is not found or it will return the index (position)
 value where the topic resides in the array. If the topic was not found, the function will return back to
 "add_depend", letting the user know that the topic they entered does not exist. The process continues by calling
 search using 'dependency'.

 If both vertices were found in the adjacency list then the dependency topic is "added" to the vertex's (topic's)
 edge list. I say "added" since although an edge node will be created, the node will not contain an actual copy of the
 corresponding vertex data. Instead, each edge node contains a variable "vertex" that is set to the position where
 the dependency topic resides in the array. Since the edge list is a LLL, adding edge nodes will occur at the beginning
 so that there is no need for a traversal.

 Each vertex_node contains an edge_node head pointer that points to its corresponding edge list. When a dependency is set
 the function will check the value of the head pointer. If the head pointer is null, the head pointer is set to a new
 edge_node, the edge node's vertex variable will be set to the dependency topic position (depend_match) and the next pointer
 will be set to null. If the head pointer for the 'topic' vertex is not null, the new edge_node gets added at the beginning of
 the LLL. */

int graph::add_edge(const char topic[], const char dependency[])
{
    edge_node * current;
    int vertex_match;
    int depend_match;

    vertex_match = search(topic); //Checks to see if the topic exists as a vertex

    if (vertex_match == -1)
    {
        return 0;
    }
    else
    {
        depend_match = search(dependency); //Checks to see if the dependency exists as a vertex

        if (depend_match == -1)
        {
            return -1;
        }
        else
        {
            if(adj_list[vertex_match].head == NULL) //If the topic's head pointer is null
            {
                adj_list[vertex_match].head = new edge_node;
                adj_list[vertex_match].head->vertex = depend_match; //Edge node's vertex variable gets set to the dependency vertex position
                adj_list[vertex_match].head->next = NULL;
            }
            else
            {
                current = adj_list[vertex_match].head;
                adj_list[vertex_match].head = new edge_node;
                adj_list[vertex_match].head->vertex = depend_match;
                adj_list[vertex_match].head->next = current;
            }
            return 1;
        }
    }
}


/*This is a simple search function that searches through the array of vertices looking for a
 vertex that matches the provided search topic. If an item is found, the function returns the position in the
 array back to the calling function. This function is used often when adding a dependency (add_edge) or checking
 to make sure a item is added that already exists. */

int graph::search(const char search_topic[])
{

    for (int i = 0; i < index; i++)
    {
        if (strcmp(adj_list[i].data.topic, search_topic) == 0)
        {
                return i;
        }
    }
    return -1;
}


/*This function takes in a character array from main that contains a possible "topic" identifier. It also takes an
 empty array of vertex_info objects so that vertex info associated with the topic's edge list can be added to the array
 for displaying them back in main. The function first passes 'topic' into the search function to see if a matching vertex exists.
 If a vertex is found, then the found variable will be set to the array position where it resides. The edge_node 'current' pointer
 is then set to the head pointer of the matching vertex. The current pointer, results array and a count variable are then passed
 into the recursive function "retrieve_graph". The recursive function will copy all the vertex information associated with the matching
 vertex's edge list into the array. In additon, the count integer will be updated as items are copied. Once the recursive
 function is complete, this function returns count back to the main function "search_depend" which utlizes the value for display certain
 messages / data. */

int graph::retrieve_adj(const char topic[], vertex_info results[])
{
    int count = 0;
    int found;
    edge_node * current;

    found = search(topic); //Checks to see if the topic exists as a vertex

    if (found == -1)
    {
        return -1;
    }
    else
    {
        current = adj_list[found].head; //Current pointer is set to the head of the found vertex's edge list
        retrieve_graph(current, results, count);
    }
    return count;
}


/*This function takes in a character array from main that contains a possible "topic" identifier. The function first passes 'topic' into
 the search function to see if a matching vertex exists. If a vertex is found, then the found variable will be set to the array position
 where it resides. The edge node current pointer is set to the found vertex's head pointer before the found vertex and the current pointer
 are passed in the recursive function display_graph() to carry out the depth-first display. After the recursion is complete, a for loop is used
 to set all the flags in the adjacency list back to false. */

int graph::display(const char topic[])
{
    int found;
    edge_node * current;

    found = search(topic);
    if (found == -1)
    {
        return 0;
    }
    else
    {
        current = adj_list[found].head;
        display_graph(adj_list[found], current);

        for (int i = 0; i < index; i++)
        {
            adj_list[i].flag = false;
        }
        return 1;
    }
}


/*This function takes in two vertex objects that are passed as reference. This function is used in order to
 generate a deep copy of the data in each object. Since the topic variable utilizes a dynamic character array, the memory
 space of the "to" object is assigned a new char array value that is exactly the size of the "from" topic. Once the memory
 is allocated, the value of topic associated with the "from" object is copied to the new memory space of the "to" object.
 This function is used in a variety of places including: add_vertex, add_edge, retrieve_graph. */

void graph::copy(vertex_info &to_vertex, vertex_info &from_vertex)
{
    to_vertex.topic = new char[strlen(from_vertex.topic)+1];
    strcpy(to_vertex.topic, from_vertex.topic);
}


/*This function is the recursive portion mentioned in the retrieve_adj function comment above. This funtion takes in an edge_node pointer,
 an array of vertex_info objects and a count variable passed as reference. The edge_node current pointer was set to a matching vertex's head
 pointer before being passed into this function. If current is null, then the chosen vertex has no nodes in its edge list. This means that
 the user has not set any dependencies to the chosen vertex. If current is not null, the information accessed with each edge list
 vertex variable is copied from the adjacency list into the results array and the count variable is incremented. The function is then called
 again with current being set to current->next. The process repeats itself until current is equal to null, reaching the end of the chosen
 vertex's edge list. */

void graph::retrieve_graph(edge_node * current, vertex_info results[], int& count)
{
    if (current)
    {
        copy(results[count], adj_list[current->vertex].data); //Copies the data into the results array
        count++;
        retrieve_graph(current->next, results, count); //Sets current to current->next on next iteration
    }
}


/*Displays information using a depth-first traversal. Takes in a vertex_node and a edge_node current pointer. Those value are set by the
 wrapper function "display" before being passed into this function. NOTE: Likely not implemented not properly */

void graph::display_graph(vertex_node& start, edge_node * current)
{
    if (start.flag != true)
    {
        if (current == NULL)
        {
            cout << start.data.topic << endl;
            start.flag = true;
        }
        else
        {
            cout << start.data.topic << endl;
            start.flag = true;
            display_graph(adj_list[current->vertex], adj_list[current->vertex].head);
        }

    }
}
