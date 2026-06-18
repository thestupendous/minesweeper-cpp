#include "../include/declarations.h"

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
void printBoard(char board[maxLen][maxHeight],bool first) {
	cout << '\n';
	if (!first) {
		for(unsigned i{0};i<maxLen;i++) {
			for(unsigned j{0};j<maxHeight;j++) {
				if (board[i][j]=='0') 
					cout << ' ' << ' ';
				else
				 cout << board[i][j] << ' ' ;
			}
			cout << "|\n";
		}
		return;
	}

	for(unsigned i{0};i<maxLen;i++) {
		for(unsigned j{0};j<maxHeight;j++) {
			cout << board[i][j] << ' ' ;
		}
		cout << "|\n";
	}
}

bool onMine(unsigned inpX,unsigned inpY,const unsigned minesList[][2]) {
	for(unsigned i{0};i<noOfMines;i++)
		if (inpX==minesList[i][0] && inpY==minesList[i][1])
			return true;
	return false;
}
