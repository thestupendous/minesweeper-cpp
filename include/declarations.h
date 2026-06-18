#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include<iostream>
#include<random>
#include<queue>
#include<string>
#include<unordered_map> // for visited map for exploreValley()
#include<utility>  // for pair
using namespace std;

/* initializing game control variables  */
const unsigned maxLen=4, maxHeight=4, noOfMines=2;

void printBoard(char a[maxLen][maxHeight],bool first=false); 
void findNumbers(char a[maxLen][maxHeight]); 
bool onMine(unsigned inpX,unsigned inpY,const unsigned minesList[][2]);
void exploreValley(char gameBoard[maxLen][maxHeight],
		char displayBoard[maxLen][maxHeight], const unsigned &inpX, 
		const unsigned &inpY, unsigned &valleyCount, unsigned &localValleyCount);
// hashString() macro for converting pair of int to string to act as key for visited map
#define hashString(a, b)   std::to_string(a) + "," + std::to_string(b) 


#endif
