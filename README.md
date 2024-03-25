# sudokoSolver

Implementation of Leetcode question 37, in C++.

This program helps visualize how the algorithm is solving the given sudoku puzzle.
Everytime the printPuzzle function is invoked it resets the position of the grid to coordinates (0,0) which overwrites the existing puzzle and helps in visualization.
There is a 50 millisecond delay before invoking the printPuzzle function after any change is made to the grid.


compilation:
g++ --std=c++11 -o sudoku main.cpp
