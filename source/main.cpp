/*
 Name: Joel Graham 
 Course: CS 163
 Programming Assignment #5

 File: main.cpp

 Purpose: This program simulates a topic / dependency graph. Each topic will be passed into
 the corresponding ADT which handles storage and manipulation of the data. Each topic will be stored in one
 data structure, adjacency list. The topics (vertices) are inserted into the adjacency list starting at element zero
 in the array. The user has the option to add a topic (add_vertex), set a dependency (add_edge), view dependencies
 associated with a particular topic (retrieve_adj) and display the topics using a depth first traversal method starting
 at a user defined postion.

 Input: When executing this program, a_graph (graph.h) object is created as well as a vertex_info object
 that passes the user information into the corresponding ADT. The data provided to the graph is managed by the struct
 "vertex_info" (See vertex_info.h). The overall structure of the program back-end is managed by the graph class (graph.h / graph.cpp).

 Output: The topics (vertices) can be displayed using a depth-first traversal method. The user is prompted to enter a topic in which to start
 from. If there is a vertex matching the topic, the recursive display will take place.

 All additional output comes from this main.cpp file and relates to the user menu and various user prompts.
 */


#include "graph.h"
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CHAR = 101;

void call_menu(void);
char read_input(const char prompt[]);
void run_input(char command, graph& a_graph);
void read_string (const char prompt[],char input_string[], int max_char);
void add_topic(graph& a_graph);
void add_depend(graph& a_graph);
void search_depend(graph& a_graph);
void display(graph& a_graph);

/*The function primarily handles how the client side of the program is structured. After declaring some class objects and other local variables, the function
 proceeds to displaying the menu screen. User input from the menu is processed through the function 'read_input' before passing 'input' and the object 'a_graph'
 as an argument into the 'run_input' function to perform additional processes. When the user is ready to quit the program, the input of 'q' will cause
 the program to terminate. */

int main ()
{
    graph a_graph;
    char input;

    call_menu();
    input = read_input("Please enter an option from the list: ");
    while (input != 'q')
    {
        run_input(input, a_graph);
        call_menu();
        input = read_input("Please enter an option from the list: ");
    }
    return 0;
}

//Displays the menu options to the user.
void call_menu(void)
{
	cout << "\nWelcome to Graph Creator!" << endl
    << "A. Add a Topic" << endl
    << "S. Set a Dependency" << endl
    << "V. View a topic's dependencies" << endl
    << "D. Display - Depth First" << endl
    << "Q. Quit the program" << endl << endl;
}


/* Accepts a prompt from the main() function and displays it. Accepts user input, converts it to lower case
and passes it back to the main() function. */

char read_input(const char prompt[])
{
	char cmd;
	cout << prompt;
	cin >> cmd;

	cin.clear();
	cin.ignore(100, '\n');
	return tolower(cmd);
}


/* User input and object 'a_graph' are passed into the function. A switch statement is used to process
 the command argument. The object is passed to this function and then passed again to add_topic in order
 to start adding topics (vertices). The objects also get passed as references into add_depend, search_depend
 and display functions in order to have access to the class member functions. Any command other than the ones
 outlined in the menu is considered invalid and it returns back to main() */

void run_input(char command,graph& a_graph)
{
	switch (command)
        {
            case 'a': add_topic(a_graph);
                break;
            case 's': add_depend(a_graph);
                break;
            case 'v': search_depend(a_graph);
                break;
            case 'd': display(a_graph);
                break;
        default: cout << "\nInvalid option, please select again." << endl;
            break;
        }
}


/* Prompts the user to enter a topic for the graph. The vertex_info object is then passed into the table class
 member function "add_vertex" for insertion into the adjacency list. */

void add_topic(graph& a_graph)
{
    vertex_info a_vertex;
    char topic[MAX_CHAR];
    int duplicate;
    int bounds;

    read_string("\nPlease enter a topic (Ex. Linear Linked List): ",topic,MAX_CHAR);

    duplicate = a_graph.search(topic);

    if (duplicate != -1)
    {
        cout <<"\nThe topic you entered already exists" << endl;
    }
    else
    {
        a_vertex.topic = new char[strlen(topic)+1];
        strcpy(a_vertex.topic, topic);

        bounds = a_graph.add_vertex(a_vertex);
        if (bounds == 0)
        {
            cout << "\nSorry, graph has reached it's maximum size" << endl;
        }
    }
}


/* Prompts the user to enter a topic and a dependency. The two character arrays get passed to the
 add_edge function which determines if the topic / dependency exists before setting the dependency
 (adding it to the chosen topic's edge list). */

void add_depend(graph& a_graph)
{
    char topic[MAX_CHAR];
    char depend[MAX_CHAR];
    int match;

    read_string("\nPlease enter a Topic (Ex. Linear Linked List): ",topic,MAX_CHAR);
    read_string("\nPlease enter a Dependency (Ex. Pointers): ",depend,MAX_CHAR);

    match = a_graph.add_edge(topic, depend);

    if (match == 0)
    {
        cout << "\nThe topic '" << topic << "' does not exist, please add it to the graph" << endl;
    }
    else if(match == -1)
    {
        cout << "\nThe dependency '" << depend << "' does not exist, please add it to the graph" << endl;
    }
}


/* Prompts the user to enter a topic. The character array gets passed to the
 retrieve_adj function which determines if the topic exists before calling a recursive
 function that copies all the vertex information relating to the topic's edge list. The
 resulting edge list (adjacent nodes to the topic) are then displayed out to the user. */

void search_depend(graph& a_graph)
{
    int size;
    vertex_info results[GRAPH_SIZE];
    char topic[MAX_CHAR];

    read_string("\nPlease enter a topic (Ex. Linear Linked List): ",topic,MAX_CHAR);

    size = a_graph.retrieve_adj(topic, results);

        if (size == -1)
        {
            cout << "\nThe topic '" << topic << "' does not exist, please add it to the graph" << endl;
        }
        else if(size == 0)
        {
            cout << "\nThe topic '" << topic << "' currently has no dependencies associated with it" << endl;
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                cout << "\nDependency " << (i+1) << ": " << results[i].topic << endl;
            }
        }
}


/*Prompts the user to enter a topic. The character array gets passed to the
 a_graph.display function which determines if the topic exists before calling
 the depth-first display recursive function. */

void display(graph& a_graph)
{
    int check;
    char topic[MAX_CHAR];

    read_string("\nPlease enter a topic (Ex. Linear Linked List): ",topic,MAX_CHAR);

    check = a_graph.display(topic);
    if(check == 0)
    {
        cout << "\nThe topic '" << topic << "' does not exist!" << endl;
    }
}

/*This function accepts a prompt, a string of characters and a max length in which to process user input. Essentially, before the data is stored into
 and object, it is cut down to it's approximate size since the user is only allowed a certain number of characters for each data field. */

void read_string (const char prompt[],char input_string[], int max_char)
{
	cout << prompt;
	cin.get(input_string, max_char, '\n');
	while(!cin)
	{
		cin.clear ();
		cin.ignore (100, '\n');
		cin.get(input_string, max_char, '\n');
	}

	cin.clear();
	cin.ignore (100, '\n');
}
