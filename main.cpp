#include<iostream>
#include<random>
#include<string>
using namespace std;

/* initializing control variables  */
const unsigned maxLen=10, maxHeight=10, noOfMines=20;

void printBoard(char a[maxLen][maxHeight]); 
void findNumbers(char a[maxLen][maxHeight]); 
int main() {

	/* defining boards  */
	char gameBoard[maxLen][maxHeight];
	char displayBoard[maxLen][maxHeight];

	/* initializing main board  */
	for(unsigned i{0};i<maxLen;i++)
		for(unsigned j{0};j<maxHeight;j++)
			gameBoard[i][j] = '.';

	/* initializing display board  */
	for(unsigned i{0};i<maxLen;i++)
		for(unsigned j{0};j<maxHeight;j++)
			displayBoard[i][j] = '.';

	/* initializing mines locations     */
	unsigned minesList[noOfMines][2];
	unsigned x{0},y{0};
	try {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distX(0, maxHeight-1);
		std::uniform_int_distribution<int> distY(0, maxLen-1);
		x = distX(gen);
		y = distY(gen);
		for (unsigned i{0};i<noOfMines;i++) {
			while( gameBoard[x][y] != '.' ){
				x = distX(gen);
				y = distY(gen);
			}
			minesList[i][0] = x;
			minesList[i][1] = y;
			gameBoard[x][y] = '*';
		}

	} catch (const std::exception& e) {
		std::cerr << "Random generation error: " << e.what() << "\n";
		return 1;
	}
	// printing all mines locations
	cout << "There are " << noOfMines << " mines.\n";
	cout << "All mines coordinates -\n";
	for(unsigned i{0};i<noOfMines;i++)
		cout << "(" << minesList[i][0] << ',' << minesList[i][1] << ") ";
	cout<<'\n';


	printBoard(displayBoard);
	printBoard(gameBoard);
	/* finding adjescency numbers of mines neighbouring
	 every cell, and updating board  */
	findNumbers(gameBoard);
	printBoard(gameBoard);

	return 0;
}
void findNumbers(char board[maxLen][maxHeight]) {
	unsigned number{0};
	for(int i{0};i<maxHeight;i++) {
		for(int j{0};j<maxLen;j++) {
			if(board[i][j]=='*') continue;
			number=0;
			// upar
			if(i-1 >= 0) {
				if(j-1 >=0) 
					if(board[i-1][j-1]=='*') number++;
				if(board[i-1][j]=='*') number++;
				if(j+1 < maxLen)
					if(board[i-1][j+1]=='*') number++;
			}
			// same height
			{
				if(j-1 >=0) 
					if (board[i][j-1]=='*') number++;
				if(j+1 < maxLen) 
					if(board[i][j+1]=='*') number++;
			}
			// niche
			if(i+1 < maxHeight) {
				if(j-1 >=0 && board[i+1][j-1]=='*') number++;
				if(board[i+1][j]=='*') number++;
				if(j+1 < maxLen && board[i+1][j+1]=='*') number++;
			}
			board[i][j] = '0'+number;
		}
	}

}
void printBoard(char board[maxLen][maxHeight]) {
	cout << '\n';
	char symbol{','};
	unsigned count{0};

	for(unsigned i{0};i<maxLen;i++) {
		for(unsigned j{0};j<maxHeight;j++) {
			symbol = board[i][j];
			if(symbol=='*') count++;
			cout << symbol<< ' ' ;
		}
		cout << "|\n";
	}
}

