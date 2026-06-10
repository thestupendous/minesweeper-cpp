# Minesweeper
classic minesweeper game, written cleanly in Mordern C++

## Documentation
### Plan
- `maxLen`, `maxHeight` for holding size of the board
- `noOfMines` for holding count of totoal mines
- two boards, one to hold mines and their neighbouring numbers (1,2,3...7), other to hold the visible board (rendering mines, marked for mine, empty cell, etc.)
- `displayBoad` has 3 types of symbols -
    - '\*' - to represent mine
    - '.' - to represent unexplored cell
    - A number in the range [0,9) - to represent numbered cell.
- `gameBoad` has 2 types of symbols -
    - '\*' - to represent mine
    - A number in the range [0,9) - to represent numbered cell.
- Functions -
  - `placeMines()` - randomly place mines on board (performing checks etc.)
  - `playGame()` - take progressively user inputs, perform game actions etc.
  - `exploreValley()` - keep revealing empty cells, where there are no mines on them/ around them.
    A valley is an area where there are no surrounding mines. This is often the first area that gets explored whenever we usually start a minesweeper game.
    Similarly there are many valleys that normally get formed in the game board, and discovering them gives another great enthusiasm in solving the game XD.


### What's being used
- Using mt19937() of <random> library for modern c++ approach to using random numbers.
- Coder Ball Knowledge: using directly (gameBoard\[i-1]\[j]>'0') directly for checking a numbered cell which is not zero (when exploring valleys) and not checking if it's '\*' or '.' because \* and . already come before 0 in ASCII.
- usage of STRING to INT map for visited map - TODO - details
- `hashString()` macro for converting pair of INT's to STRING to act as key for visited map


### To Add (later)
- no global variables for size of board, number of mines 
- vectors arrays instead of static matrices (for avoiding global use of size constants)
