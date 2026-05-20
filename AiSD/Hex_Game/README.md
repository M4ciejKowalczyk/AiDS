# Hex Game State Analyzer

## Overview
This project was created for the **Algorithms and Data Structures** coursework and focuses on evaluating the state of a board in **Hex** (a strategy game invented by Piet Hein and John Nash). 

The core challenge was to mathematically represent a hexagonal grid and determine winning states (continuous paths connecting opposite edges for Red or Blue players) without relying on any external pathfinding libraries or the C++ Standard Template Library (STL).

## Features & Algorithms
* **Hexagonal Grid Representation:** Mapping a non-standard 2D hexagonal board (up to 11x11 dimensions) into memory using custom structural arrays and managing the coordinate system.
* **Custom Graph Traversals:** Implementation of custom Depth-First Search (DFS) / Breadth-First Search (BFS) algorithms across the hexagonal topology to check for continuous, unbroken paths between player-specific edges.
* **Game State Validation:** Logical checks to verify pawn counts, identify if a board state is possible, and confirm whether the game has reached a definite "game over" state.
* **Predictive Game Logic:** Algorithms evaluating future game states to determine whether a naive or perfect player can achieve victory within the next one or two turns.
