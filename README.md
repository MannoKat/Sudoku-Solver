Sudoku solver using hidden/naked pairs, triples, and hidden singles algorithm.
Sudoku Solver in C
Overview
This Sudoku Solver is a C program designed to solve Sudoku puzzles using a combination of algorithms, including hidden/naked pairs, triples, and hidden singles. The program is implemented in C for simplicity and efficiency.

Features
Solve Sudoku puzzles using advanced techniques like hidden/naked pairs, triples, and hidden singles.
Command-line interface for easy interaction.
Supports input of Sudoku puzzles in a simple text format.
Getting Started
Prerequisites
Make sure you have a C compiler installed on your system (e.g., GCC).
Building the Solver
Clone the repository:

bash
Copy code
git clone https://github.com/MannoKat/Sudoku-Solver.git
Navigate to the project directory:

bash
Copy code
cd Sudoku-Solver
Compile the C program:

bash
Copy code
gcc sudoku_solver.c -o sudoku_solver
Usage
Run the solver:

bash
Copy code
./sudoku 530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079

Algorithms
Hidden/Naked Pairs
Detect and eliminate candidates for cells by identifying hidden/naked pairs.
Hidden Triples
Extend the hidden pairs concept to triples.
Hidden Singles
Fill in cells where a number is the only candidate.

Contributing
Contributions are welcome! If you have ideas for improvements or find any issues, please open an issue or submit a pull request.
