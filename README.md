# Sudoku Solver in C

This is a simple Sudoku solver implemented in C, capable of solving Sudoku puzzles using hidden/naked pairs, triples, and hidden singles algorithms.
This is also my program did by me and my instructor
## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [How to Use](#how-to-use)
- [Algorithms](#algorithms)
- [Contributing](#contributing)

## Introduction

This Sudoku solver is designed to solve Sudoku puzzles using advanced techniques such as hidden/naked pairs, triples, and hidden singles algorithm. It is developed in C for efficiency and performance.

## Features

- Solves Sudoku puzzles using hidden/naked pairs, triples, and hidden singles.
- Efficient C implementation for fast solving.
- Easy-to-understand codebase.

## How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/MannoKat/Sudoku-Solver.git
   cd Sudoku-Solver

2. Compile the code:

Compiling:
   ```bash
   make
   ./sudoku <sudoku_string>
   ```
## Algorithms
The solver employs the following algorithms to solve Sudoku puzzles:

Hidden Triples: Identifies pairs of candidate numbers in a row, column, or block where the numbers are confined to three cells.

Naked Triples: Similar to hidden triples, but instead of eliminating possibilities, it directly assigns the values to the tripled cells.

Hidden Pairs: Identifies pairs of candidate numbers in a row, column, or block where the numbers are confined to two cells.

Naked Pairs: Similar to hidden pairs, but instead of eliminating possibilities, it directly assigns the values to the paired cells.

Hidden Singles: Identifies cells where there is only one candidate number remaining.

## Contributing
If you find any issues or have suggestions for improvements, feel free to open an issue or create a pull request.

Happy Sudoku solving!😊😊
