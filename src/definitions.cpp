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
		cout << '\n';
		return;
	}

	for(unsigned i{0};i<maxLen;i++) {
		for(unsigned j{0};j<maxHeight;j++) {
			cout << board[i][j] << ' ' ;
		}
		cout << "|\n";
	}
	cout << '\n';
}

bool onMine(unsigned inpX,unsigned inpY,const unsigned minesList[][2]) {
	for(unsigned i{0};i<noOfMines;i++)
		if (inpX==minesList[i][0] && inpY==minesList[i][1])
			return true;
	return false;
}

// if stepped on a valley
// exploreValley() - explore the valley
// need to call BFS
void exploreValley(char gameBoard[maxLen][maxHeight],
	char displayBoard[maxLen][maxHeight], const unsigned &inpX, 
	const unsigned &inpY, unsigned &valleyCount,
	unsigned &localValleyCount) {
  	if(gameBoard[inpX][inpY]  =='0') {
  		unordered_map<string,unsigned short> visited;
  		std::queue<pair<unsigned,unsigned>> valleyQueue;
  		valleyQueue.push({inpX,inpY});
  		localValleyCount=0;
  		while( !valleyQueue.empty() ) {
  			// keep marking each non zero and non mine padosi on
  			// the display board, and keep pushing all '0's on to
  			// the valley queue.
  			int i(valleyQueue.front().first), j(valleyQueue.front().second);
  			// upar
  			if(i-1 >= 0) {
  				if(j-1 >=0 && visited[hashString(i-1,j-1)]!=1) {
  					if(gameBoard[i-1][j-1]=='0' ) {
  						valleyQueue.push({i-1,j-1});
  						displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
  					}
  					else if(gameBoard[i-1][j-1]>'0') {
  						displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
  					}
  					visited[hashString(i-1,j-1)] = 1;
  					localValleyCount++;
  				}
  				if(visited[hashString(i-1,j)]!=1) {
  					if (gameBoard[i-1][j]=='0') {
  						valleyQueue.push({i-1,j});
  						displayBoard[i-1][j]=gameBoard[i-1][j];
  					}
  					else if(gameBoard[i-1][j]>'0' && visited[hashString(i-1,j)]!=1) {
  						displayBoard[i-1][j]=gameBoard[i-1][j];
  					}
  					visited[hashString(i-1,j)] = 1;
  					localValleyCount++;
  				}
  				if(j+1 < maxLen && visited[hashString(i-1,j+1)]!=1) {
  					if(gameBoard[i-1][j+1]=='0') {
  						valleyQueue.push({i-1,j+1});
  						displayBoard[i-1][j+1]=gameBoard[i-1][j+1];
  					}
  					else if(gameBoard[i-1][j+1]>'0'){
  						displayBoard[i-1][j+1]=gameBoard[i-1][j+1];
  					}
  					visited[hashString(i-1,j+1)] = 1;
  					localValleyCount++;
  				}
  			}
  			// same height
  			{
  				if(j-1 >=0 && visited[hashString(i,j-1)]!=1) {
  					if (gameBoard[i][j-1]=='0') {
  						valleyQueue.push({i,j-1});
  						displayBoard[i][j-1]=gameBoard[i][j-1];
  					}
  					else if (gameBoard[i][j-1]>'0'){
  						displayBoard[i][j-1]=gameBoard[i][j-1];
  					}
  					visited[hashString(i,j-1)] = 1;
  					localValleyCount++;
  				}
  				if(j+1 < maxLen && visited[hashString(i,j+1)]!=1) {
  					if(gameBoard[i][j+1]=='0') {
  						valleyQueue.push({i,j+1});
  						displayBoard[i][j+1]=gameBoard[i][j+1];
  					}
  					else if(gameBoard[i][j+1]>'0'){
  						displayBoard[i][j+1]=gameBoard[i][j+1];
  					}
  					visited[hashString(i,j+1)] = 1;
  					localValleyCount++;
  				}
  			}
  			// niche
  			if(i+1 < maxHeight) {
  				if(j-1 >=0 && visited[hashString(i+1,j-1)]!=1) {
  					if (gameBoard[i+1][j-1]=='0') {
  						valleyQueue.push({i+1,j-1});
  						displayBoard[i+1][j-1]=gameBoard[i+1][j-1];
  					}
  					else if(j-1 >=0 && gameBoard[i+1][j-1]>'0'){
  						displayBoard[i+1][j-1]=gameBoard[i+1][j-1];
  					}
  					visited[hashString(i+1,j-1)] = 1;
  					localValleyCount++;
  				}
  				if (visited[hashString(i+1,j)]!=1) {
  					if(gameBoard[i+1][j]=='0') {
  						valleyQueue.push({i+1,j});
  						displayBoard[i+1][j]=gameBoard[i+1][j];
  					}
  					else if(gameBoard[i+1][j]>'0'){
  						displayBoard[i+1][j]=gameBoard[i+1][j];
  					}
  					visited[hashString(i+1,j)] = 1;
  					localValleyCount++;
  				}
  				if(j+1 < maxLen && visited[hashString(i+1,j+1)]!=1) {
  					if (gameBoard[i+1][j+1]=='0') {
  						valleyQueue.push({i+1,j+1});
  						displayBoard[i+1][j+1]=gameBoard[i+1][j+1];
  					}
  					else if(j+1 < maxLen && gameBoard[i+1][j+1]>'0'){
  						displayBoard[i+1][j+1]=gameBoard[i+1][j+1];
  					}
  					visited[hashString(i+1,j+1)] = 1;
  					localValleyCount++;
  				}
  			}
  			if (displayBoard[i][j] == '.') displayBoard[i][j] = gameBoard[i][j];
  			valleyQueue.pop();
  		}
  		valleyCount += localValleyCount;
  	}
}

