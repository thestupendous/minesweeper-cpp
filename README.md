# Minesweeper
classic minesweeper game, written cleanly in Mordern C++

## documentation
### Plan
- maxLen, maxHeight for holding size of the board
- noOfMines for holding count of totoal mines
- two boards, one to hold mines and their neighbouring numbers (1,2,3...7), other to hold the visible board (rendering mines, marked for mine, empty cell, etc.)
- Functions -
  - placeMines() - randomly place mines on board (performing checks etc.)
  - playGame() - take progressively user inputs, perform game actions etc.
  - exploreValley() - keep revealing empty cells, where there are no mines on them/ around them.

### What's being used
- Using mt19937() of <random> library for modern c++ approach to using random numbers.

### To Add (later)
- no global variables for size of board, number of mines 
- vectors arrays instead of static matrices (for avoiding global use of size constants)
