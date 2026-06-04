#include<iostream>
#include<random>
#include<string>
using namespace std;

/* initializing control variables  */
const unsigned maxLen=10, maxHeight=10, noOfMines=20;

void printBoard(char a[maxLen][maxHeight]); 
int main() {

	/* defining boards  */
	char gameBoard[maxLen][maxHeight];
	string displayBoard[maxLen][maxHeight];

	/* initializing mines locations     */
	unsigned minesList[noOfMines][2];
	unsigned x{0},y{0};
	try {
		// 1. Create a random device for seeding (may use hardware entropy)
		std::random_device rd;
		// 2. Initialize Mersenne Twister engine with the seed
		std::mt19937 gen(rd()); // High-quality PRNG
														// 3. Define a uniform integer distribution in range [1, 100]
		std::uniform_int_distribution<int> distX(0, maxLen-1);
		std::uniform_int_distribution<int> distY(0, maxHeight-1);
		  cout<< "log Before\n";
		for (unsigned i{0};i<noOfMines;i++) {
			minesList[i][0] = distX(gen);
			minesList[i][1] = distY(gen);
		}
		  cout<< "log After\n";

	} catch (const std::exception& e) {
		std::cerr << "Random generation error: " << e.what() << "\n";
		return 1;
	}
	// printing all mines locations
	for(unsigned i{0};i<noOfMines;i++)
		cout << "(" << minesList[i][0] << ',' << minesList[i][1] << ") ";
	cout<<'\n';


	/* initializing main board  */
	for(unsigned i{0};i<maxLen;i++)
		for(unsigned j{0};j<maxHeight;j++)
			gameBoard[i][j] = '.';
	// placing mines on main board
	for(unsigned i{0};i<noOfMines;i++)
		// putting Ø character for mines
		gameBoard[minesList[i][0]][minesList[i][1]] = '*'; 

	// printing all mines locations on board
	for(unsigned i{0};i<noOfMines;i++)
		cout << "(" << gameBoard[minesList[i][0]][minesList[i][1]] << ") ";
	cout<<'\n';

	printBoard(gameBoard);

	return 0;
}

void printBoard(char board[maxLen][maxHeight]) {
		cout << '\n';
	
	for(unsigned i{0};i<maxLen;i++) {
		for(unsigned j{0};j<maxHeight;j++)
			cout << board[i][j];
		cout << "|\n";
	}
}

