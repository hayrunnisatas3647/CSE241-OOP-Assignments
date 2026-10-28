# HW3 - Weighted Graph

## Description

This project implements a weighted, undirected graph in C++ using an adjacency matrix.

It was developed for the CSE241 Object-Oriented Programming course at Gebze Technical University.

The project focuses on object-oriented programming concepts, especially constructors, operator overloading, and graph operations.

## Features

- Edge and Graph classes.
- Graph representation using an adjacency matrix.
- Supports up to 20 vertices.
- Multiple constructors, including delegating constructors.
- Static default edge weight.
- Graph union and difference operations.
- Graph comparison operations.
- Graph complement.
- Prefix and postfix increment operators for adding vertices.
- Vertex labels and edge weight access.
- Calculates vertex degrees, edge counts, and total graph weight.
- Reads graph data from a text file.

## Operator Overloading

The project implements several overloaded operators:

- `+` : Combines graphs or adds an edge.
- `-` : Removes edges or creates a complement graph.
- `==` and `!=` : Compares graphs or edges.
- `<` : Compares edge weights.
- `()` : Accesses the weight between two vertices.
- `[]` : Accesses and modifies vertex labels.
- `++` : Adds a vertex using prefix or postfix increment.
- `<<` and `>>` : Outputs and inputs edges.

## How to Run

Compile the program:

`g++ Graph.cpp -o Graph.exe`

Make sure the required `roads.txt` input file is in the same working directory.

Run on Windows:

`.\Graph.exe`

The program demonstrates graph constructors, operations, and file input.

## Concepts Used

- Classes and objects
- Constructor overloading
- Delegating constructors
- Operator overloading
- Static members
- Adjacency matrices
- Vectors
- File handling

## Technologies

- C++
- Visual Studio Code
- G++ Compiler
