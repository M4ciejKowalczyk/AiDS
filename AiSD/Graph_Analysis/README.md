# Graph Algorithms & Custom Data Structures

## Overview
This project was developed as part of the **Algorithms and Data Structures** coursework. The primary objective and main technical challenge of this assignment was the **strict prohibition of the C++ Standard Template Library (STL)**. 


## Features & Implemented Structures
* **Custom Dynamic Array (`Vector`):** A from-scratch implementation of a dynamically resizing array (analogous to `std::vector`), handling automatic capacity expansion and memory reallocation.
* **Custom FIFO Queue (`Queue`):** A custom queue data structure (analogous to `std::queue`) used to manage elements during graph traversals efficiently.
* **Graph Representation (`Graph`):** Implementation of a graph using an adjacency list approach, built entirely upon the custom `Vector` class.
* **Graph Traversals:** Features Breadth-First Search (BFS) routing utilizing the custom `Queue` to explore nodes, find paths, or determine connected components.

## Graph Analytics & Algorithms
The core engine of the project analyzes the structural properties of the provided graphs. The program calculates the following metrics:
* **Vertex Degrees:** Calculating the number of edges incident to each vertex in the graph.
* **Connected Components:** Identifying and counting all isolated subgraphs (components) within the main graph structure.
* **Bipartite Check:** Verifying whether the graph is bipartite (i.e., its vertices can be divided into two disjoint sets such that no two adjacent vertices share the same set).
* **Graph Coloring:** Applying coloring methods to assign colors to vertices ensuring no adjacent vertices share the same color.
* **Eccentricity:** Calculating the maximum shortest-path distance from a given vertex to any other reachable vertex in the graph.

## Input Data Format
The program reads graph definitions from a standard input text file, which must be structured as follows:
* **First line:** A single integer representing the total number of graphs to be processed.
* **Subsequent lines (per graph):** * An integer `n` representing the total number of vertices in the graph.
  * Followed by lists of neighbors for each successive vertex (vertices are numbered from `1` to `n`). 
  * A `0` is used to indicate that a specific vertex has no neighbors.

