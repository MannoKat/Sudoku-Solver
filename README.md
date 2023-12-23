# Sudoku Solver in C

This is a simple Sudoku solver implemented in C, capable of solving Sudoku puzzles using hidden/naked pairs, triples, and hidden singles algorithms.

## How to Use

1. Clone the repository:

   ```bash
   git clone https://github.com/MannoKat/Sudoku-Solver.git
   cd Sudoku-Solver
2. Compile the code:

Compiling:
   ```bash
   make
   ```
Running:
   ```bash
   ./sudoku <sudoku_string>
   ```
## Algorithms Used
The solver employs the following algorithms to solve Sudoku puzzles:

Hidden Triples: Identifies pairs of candidate numbers in a row, column, or block where the numbers are confined to three cells.

Naked Triples: Similar to hidden triples, but instead of eliminating possibilities, it directly assigns the values to the tripled cells.

Hidden Pairs: Identifies pairs of candidate numbers in a row, column, or block where the numbers are confined to two cells.

Naked Pairs: Similar to hidden pairs, but instead of eliminating possibilities, it directly assigns the values to the paired cells.

Hidden Singles: Identifies cells where there is only one candidate number remaining.

## Contributing
If you find any issues or have suggestions for improvements, feel free to open an issue or create a pull request.

Happy Sudoku solving!😊😊
