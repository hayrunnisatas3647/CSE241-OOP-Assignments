# HW1 - Reversi Game

## Description

This project is a console-based implementation of the Reversi (Othello) game, developed in C++ for the CSE241 Object-Oriented Programming course at Gebze Technical University.

The player competes against the computer by placing pieces on the board and flipping the opponent's pieces.

## Features

- Supports 8x8, 10x10, and 12x12 board sizes.
- Player vs. computer gameplay.
- Validates player moves.
- Checks all eight directions for possible moves.
- The computer selects a move that flips the maximum number of pieces.
- Skips turns when no valid moves are available.
- Calculates the final scores and determines the winner.

## How to Run

Compile the program using G++:

`g++ Reversi.cpp -o Reversi.exe`

Run the program on Windows:

`.\Reversi.exe`

Choose a board size (8, 10, or 12).

Enter moves using a row number followed by a column letter, such as `4c` or `10j`.

## Concepts Used

- Functions
- Two-dimensional arrays
- Loops and conditional statements
- Input validation
- Game logic and algorithms

## Technologies

- C++
- Visual Studio Code
- G++ Compiler
