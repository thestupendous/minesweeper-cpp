#include<iostream>
#include<random>
#include<string>
#include<queue>
#include<utility>  // for pair
using namespace std;

/* initializing control variables  */
const unsigned maxLen=4, maxHeight=4, noOfMines=1;

void printBoard(char a[maxLen][maxHeight]); 
void findNumbers(char a[maxLen][maxHeight]); 
bool onMine(unsigned inpX,unsigned inpY,const unsigned minesList[][2]);
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
	//printBoard(gameBoard);

	/* play game */
	bool finished{false},won{false};
	unsigned movesCount{0};
	unsigned playableMoves = maxHeight*maxLen - noOfMines;
	while(!finished) {
		// input coordinates
		unsigned inpX, inpY;
		do {
			cout<<"Input your move(column no, row no) : ";
			cin >> inpX >> inpY;
		} while ( displayBoard[inpX][inpY]!='.' );
		// (TODO: input validation)

		// if stepped on mine
		if(gameBoard[inpX][inpY]=='*') {
			cout<< "GAME OVER!!!!\n";
			cout << "moves: " << movesCount << '\n';
			finished=true;
			break;
		}

		// if stepped on a valley
		// need to call BFS
		if(gameBoard[inpX][inpY]=='0') {
			std::queue<pair<unsigned,unsigned>> valleyQueue;
			valleyQueue.push({inpX,inpY});
			while( !valleyQueue.empty() ) {
				// keep marking each non zero and non mine padosi on
				// the display board, and keep pushing all '0's on to
				// the valley queue.
				int i(valleyQueue.front().first), j(valleyQueue.front().second);
				// upar
				if(i-1 >= 0) {
					if(j-1 >=0) 
						if(gameBoard[i-1][j-1]=='0') {
							valleyQueue.push({i-1,j-1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
						}
						else if(gameBoard[i-1][j-1]>'0') displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
					if(gameBoard[i-1][j]=='0') {
						valleyQueue.push({i-1,j});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
					}
					else if(gameBoard[i-1][j]>'0') displayBoard[i-1][j]=gameBoard[i-1][j];
					if(j+1 < maxLen)
						if(gameBoard[i-1][j+1]=='0') {
							valleyQueue.push({i-1,j+1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
						}
					else if(gameBoard[i-1][j+1]>'0') displayBoard[i-1][j+1]=gameBoard[i-1][j+1];
				}
				// same height
				{
					if(j-1 >=0) 
						if (gameBoard[i][j-1]=='0') {
							valleyQueue.push({i,j-1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
						}
					else if (gameBoard[i][j-1]>'0') displayBoard[i][j-1]=gameBoard[i][j-1];
					if(j+1 < maxLen) 
						if(gameBoard[i][j+1]=='0') {
							valleyQueue.push({i,j+1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
						}
					else if(gameBoard[i][j+1]>'0') displayBoard[i][j+1]=gameBoard[i][j+1];
				}
				// niche
				if(i+1 < maxHeight) {
					if(j-1 >=0 && gameBoard[i+1][j-1]=='0') {
						valleyQueue.push({i+1,j-1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
					}
					else if(j-1 >=0 && gameBoard[i+1][j-1]>'0') displayBoard[i+1][j-1]=gameBoard[i+1][j-1];
					if(gameBoard[i+1][j]=='0') {
						valleyQueue.push({i+1,j});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
					}
					else if(gameBoard[i+1][j]>'0') displayBoard[i-1][j]=gameBoard[i-1][j];
					if(j+1 < maxLen && gameBoard[i+1][j+1]=='0') {
						valleyQueue.push({i+1,j+1});
							displayBoard[i-1][j-1]=gameBoard[i-1][j-1];
					}
					else if(j+1 < maxLen && gameBoard[i+1][j+1]>'0') displayBoard[i+1][j+1]=gameBoard[i+1][j+1];
				}
				valleyQueue.pop();
			}
		}

		// if stepped on number (not zero)
		if (gameBoard[inpX][inpY]!='*' && gameBoard[inpX][inpY]!='0') {
			movesCount++;
			displayBoard[inpX][inpY] = gameBoard[inpX][inpY];
			printBoard(displayBoard);
		}

		// if the game is won
		if (movesCount == playableMoves)
		{
			cout << "YOU HAVE WON THE GAME, CONGRATSSSSS!!!";
			cout << "moves: " << movesCount << '\n';
			finished=true;
			won=true;
			break;
		}
	}

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

bool onMine(unsigned inpX,unsigned inpY,const unsigned minesList[][2]) {
	for(unsigned i{0};i<noOfMines;i++)
		if (inpX==minesList[i][0] && inpY==minesList[i][1])
			return true;
	return false;
}
