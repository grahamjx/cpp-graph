##C++ - Graph ADT

###Foreword
Repos like this one contain old work that I did during my time at Portland State University. Most of these projects were completed in the Data Structures or Computer Systems Programming courses. These projects demonstrate my solid understanding of programming basics as well as familiarity with fundamental system architectures. Each project is meticulously commented and the provided design write-up discusses some of the implementation choices I made when creating these projects.

###Getting Started

Simply run the compiled executable from any unix-based terminal

```bash
  $> cd /path/to/your-project-folder
  $> ./cs-graph
  ```
Of course if you want to compile it from source a simple ```$> make run ``` from the source directory will do the trick.

###Purpose:
This program simulates a topic / dependency graph. Each topic will be passed into the corresponding ADT which handles storage and manipulation of the data. Each topic will be stored in one data structure, adjacency list. The topics (vertices) are inserted into the adjacency list starting at element zero in the array. The user has the option to add a topic (add_vertex), set a dependency (add_edge), view dependencies
associated with a particular topic (retrieve_adj) and display the topics using a depth first traversal method starting
at a user defined position.

###Input:   
When executing this program, a_graph (graph.h) object is created as well as a vertex_info object that passes the user information into the corresponding ADT. The data provided to the graph is managed by the struct "vertex_info" (See vertex_info.h). The overall structure of the program back-end is managed by the graph class (graph.h / graph.cpp).

###Output:  
The topics (vertices) can be displayed using a depth-first traversal method. The user is prompted to enter a topic in which to start
from. If there is a vertex matching the topic, the recursive display will take place.
