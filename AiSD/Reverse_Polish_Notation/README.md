# Reverse Polish Notation (RPN) Evaluator

## Overview
This project was developed as part of the **Algorithms and Data Structures** coursework. The goal was to build a mathematical expression parser and evaluator using Reverse Polish Notation (RPN, or ONP in Polish). 

A key technical constraint of this project was the **strict prohibition of the C++ Standard Template Library (STL)**. All data structures required for tokenization, parsing, and evaluation had to be implemented entirely from scratch.

## Features & Implemented Structures
* **Custom Stack & Queue:** Fully custom, dynamically allocated implementations of the Stack and Queue data structures to manage the flow of operands and operators.
* **Expression Tokenization:** A parsing mechanism used to differentiate and process operands, arithmetic operators, and mathematical functions.
* **Shunting-Yard Algorithm:** Implementation of Edsger W. Dijkstra's classic algorithm to convert infix mathematical expressions into postfix notation, taking operator precedence and associativity into account.
* **RPN Evaluation:** Real-time calculation of the parsed mathematical strings ensuring correct execution order.
