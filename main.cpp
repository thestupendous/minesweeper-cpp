#include "include/declarations.h"

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


	printBoard(displayBoard,true);

	cout << " // below board is for debugging purposes only, \n";
	cout << " // should not be used when actually playing the game\n";
	printBoard(gameBoard,true); // printing unfinished gameBoard
															// with just mines

	/* finding adjescency numbers of mines neighbouring
		 every cell, and updating board  */
	findNumbers(gameBoard);

#if 0 // printing finalised gameBoard, after updating numbers
	cout << " // below board is for debugging purposes only, \n";
	cout << " // should not be used when actually playing the game\n";
	printBoard(gameBoard,true);
#endif

	/* play game */
	bool finished{false},won{false};
	unsigned movesCount{0};
	unsigned playableMoves = maxHeight*maxLen - noOfMines;
	unsigned valleyCount{0}; // no of cells explored during exploreVally()
	unsigned localValleyCount{0};
	while(!finished) {
		// input coordinates
		unsigned inpX, inpY;
		do {
			cout<<"Input your move(column no, row no) : ";
			cin >> inpX >> inpY;
			// cout << "LOG 1: ye tha (" << inpX << ',' << inpY << ") : " << displayBoard[inpX][inpY] << '\n';
			// if(displayBoard[inpX][inpY] =='.') { break; }
			// else cout << "log 1: nahi tha .\n";
		} while ( displayBoard[inpX][inpY] !='.' );
		// (TODO: input validation)

		// if stepped on mine
		if(gameBoard[inpX][inpY]  =='*') {
			cout<< "GAME OVER!!!!\n";
			cout << "moves: " << movesCount << '\n';
			finished=true;
			break;
		}

		// if stepped on a valley
		// exploreValley() - explore the valley
		// need to call BFS
		exploreValley(gameBoard, displayBoard, inpX, inpY,
				valleyCount, localValleyCount);


		// if stepped on number (not zero)
		if (gameBoard[inpX][inpY]!='*' && gameBoard[inpX][inpY]!='0') {
			movesCount++;
			displayBoard[inpX][inpY] = gameBoard[inpX][inpY];
			// cout << "LOG: aya tha\n";
		}

		// if the game is won
		if (movesCount+valleyCount == playableMoves)
		{
			cout << "Log 2: Moves+Vc " << movesCount+valleyCount << '\n';
			cout << "YOU HAVE WON THE GAME, CONGRATSSSSS!!!";
			cout << "moves: " << movesCount << '\n';
			finished=true;
			won=true;
			break;
		} else {
			cout << "Log 2: Moves+Vc " << movesCount+valleyCount << '\n';
		}
		printBoard(displayBoard);
	}

	return 0;
}
