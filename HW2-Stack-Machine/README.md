# HW2 - Stack Machine

## Description

This project is a stack-based virtual machine developed in C++ for the CSE241 Object-Oriented Programming course at Gebze Technical University.

The program reads instructions from a text file and executes them using a stack and memory system.

## Features

- Stack with a maximum capacity of 50 integers.
- Memory containing 100 cells.
- Supports memory values between 0 and 255.
- Reads and executes up to 500 instructions.
- Supports arithmetic and stack operations.
- Supports conditional and unconditional jumps.
- Provides error handling for invalid instructions and operations.

## Supported Instructions

**Stack Operations:** PUSH, POP, DUP

**Arithmetic Operations:** ADD, SUB, MUL

**Control Flow:** JMP, JZ, JNP, HLT

**Input / Output:** INP, PRN

## Execution Options

The program supports three execution modes:

- **Option 0:** Normal execution.
- **Option 1:** Displays the stack after each instruction.
- **Option 2:** Displays both the stack and memory after each instruction.

## How to Run

Compile the program:

`g++ Stack-Machine.cpp -o Stack-Machine.exe`

Run it with an instruction file and an execution option:

`.\Stack-Machine.exe program.txt 0`

Replace `program.txt` with the name of your instruction file. Use `1` or `2` instead of `0` for additional execution details.

## Concepts Used

- Classes and objects
- Arrays
- Stack data structure
- File handling
- Command-line arguments
- Conditional statements and loops
- Error handling

## Technologies

- C++
- Visual Studio Code
- G++ Compiler
