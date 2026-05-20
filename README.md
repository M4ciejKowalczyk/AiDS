# Algorithms and Data Structures (AiSD)

## Overview
This repository contains a collection of algorithmic projects and data structures implemented entirely from scratch in C++. These projects were developed as part of the **Algorithms and Data Structures (Algorytmy i Struktury Danych)** coursework.

The defining technical challenge across all projects in this repository was a **strict prohibition of the C++ Standard Template Library (STL)**. To comply with these constraints every container used (dynamic arrays, FIFO queues, LIFO stacks, graphs) was designed and coded from scratch.


## Projects Directory
The repository is organized into subdirectories, each featuring its own source code and a project-specific description.

### [1. Custom Graph Structures & BFS](./AiSD/Graph_Analysis)
An implementation of a graph using an adjacency list model. Since standard components were banned, this project features a fully custom dynamic array (`Vector`) and a custom FIFO `Queue` used to drive optimized Breadth-First Search (BFS) graph traversals.

### [2. Reverse Polish Notation (RPN) Evaluator](./AiSD/Reverse_Polish_Notation)
A mathematical expression parser and evaluator. It implements Edsger W. Dijkstra's classic Shunting-yard algorithm to convert infix expressions into postfix notation (RPN) using a custom-built dynamic `Stack` and `Queue` to safely manage tokenized operands, operators, and functional precedents.

### [3. Hex Game State Analyzer & Pathfinding](./AiSD/Hex_Game)
A system designed to process complex grid topologies and evaluate board states for the strategy game *Hex*. It handles the mathematical mapping of a non-standard 2D hexagonal grid and implements customized graph traversal algorithms (DFS/BFS) to determine connection paths between player-specific boundaries.
