/*
 * Patrick Drumm
 * cse20212, lab1
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "C4Col.h"
#include "C4Board.h"

using namespace std;

C4Col::C4Col() {
	numDisc = 0;	// sets initial number of discs in column to zero
	maxDisc = 6;	// every column has a max of 6 discs
	playerDiscs = new char[6];	// stores value of six disc locations
	for(int i=0; i<maxDisc; i++) playerDiscs[i] = ' ';	// set initial disc value of all discs in column to empty
}

C4Col::~C4Col() {
	delete [] playerDiscs;
}

int C4Col::isFull() {
	if(numDisc==maxDisc) return(1);	// if the column is full, return a 1
	else return (0);
}

char C4Col::getDisc(int discX) {
	if(discX<0 || discX>=6)			// if not checking within bounds of the board, return error
		cout << "Error. Disc requested is out of bounds." << endl;
	else
		return(playerDiscs[discX]);	// if within board, return value of disc requested
}

int C4Col::getMaxDiscs() {
	return(maxDisc);	// return maximum number of discs for column(6)
}

void C4Col::addDisc(char newDisc) {
	if(isFull()) cout << "Sorry, but this column is full" << endl;	// displays error message if user tries to add a disc to a full column
	else playerDiscs[numDisc++] = newDisc;				// adds the correct player's disc if column is not full. This also increments the number of discs in that column by 1
}

int C4Col::getNumDisc() {
	return(numDisc);	// return the number of discs in the column
}

C4Board::C4Board() {
	numCol = 7;			// set number of columns in board to be 7
	board = new C4Col[numCol];	// create 7 columns to compose board(dynamic memory allocation)
}

C4Board::~C4Board() {
	delete [] board;
}

void C4Board::display() {
	for(int i=board[0].getMaxDiscs() - 1; i>=0; i--){	// subtract 1 from maxDisc to match array indexing. Print last element of each column first, through to the first element of each column which will be last
		cout << "| ";					// displays leftmost column barrier
		for(int j=0; j<numCol; j++){
			cout << board[j].getDisc(i) << " | ";	// displays every disc and the barrier on the right of each given disc
		}
		cout << endl;
	}
	cout << "  1   2   3   4   5   6   7" << endl;		// numbered columns for user guidance
}

void C4Board::play() {
	int userCol=0,		// column the user chooses to play disc in
		userTurn=0,	// counts up total number of turns
		miss=0,		// used to determin if user plays piece out of bounds
		isWin=0;	// boolean variable. true if a player wins the game
	string player1, player2;// users names
	// input of users' names
	cout << "You have selected two player mode!\nPlease enter the name of Player 1: ";
	cin >> player1;
	cout << "Player 2: ";
	cin >> player2;
	cout << "Here are your game piece assignments..." << endl << endl << player1 << ": X" << endl << player2 << ": O" << endl << endl;
	// game instructions printed
	cout << "To play your piece when it is your turn, simply enter the column number desired when prompted.\nPlease note: you may exit at any time by entering the value: -1\n\nLet's begin!" << endl << endl;	
	display();	// print empty board

	while(userCol != -1){
		userTurn++;		// increment total turns each time a disc is played
		if(userTurn>=43){
			cout<<"Board has filled. It's a tie!"<<endl;
			userCol=-1;
			break;
		}
		cout << "Which column would you like to play your disc?" << endl;
		miss=0;			// reset miss to 0
		if(userTurn%2 == 1) {	// true if it is player 1's turn
			do {
				if(miss>0) {cout << "Error. Please enter a number [1,7]\n";}	
				miss++;
				cout << player1 << ": ";		//prompt user for disc placement
				(cin >> userCol);			// grab the user column
			}while((userCol<1 || userCol>7)&& userCol!=-1);	//checks to make sure the disc is played within bounds of board
		}else{
			do {
				if(miss>0) cout << "Error. Please enter a number [1,7]\n";// miss>0 only after first input is collected. This ensures that the user gets to play a disc and the location can be checked by the while condition
				miss++;
				cout << player2 << ": ";		//prompt user for disc placement
				(cin >> userCol);			// grab the user column
			}while((userCol<1 || userCol>7)&& userCol!=-1);	//checks to make sure the disc is played within bounds of board
		}
		// If the user chooses to quit, display message and exit game(ie. exit while loop)
		if(userCol==-1){
			cout << "Thank you for playing!" << endl;
			break;
		}
		userCol-=1;	// Now that we have checked if user entered -1, change userCol so that it corresponds to the location in the array of columns
		// If the user plays in a full column, display error message, and then subtract a turn from total turns so that the same player may go again
		if(board[userCol].isFull()) {
			cout << "Column is full. Please try again." << endl;
			userTurn--;
		// If the user played in a valid column, add the disc to the board and check to see if they won
		}else{
			if(userTurn%2 == 1) {
				board[userCol].addDisc('X');
				isWin=didWin('X',userCol);
			}else{
				board[userCol].addDisc('O');
				isWin=didWin('O',userCol);
			}
			system("clear");	// clear the screen for clean display
			cout << player1 << ": X\n" << player2 << ": O\n\n";	// display user discs as a reminder
		}
		display();	// display the board
		// If the user wins, end the game(ie. exit the whil loop) and display a message declaring them as the winner!
		if(isWin){
			userCol=-1;
			if(userTurn%2 == 1) cout << endl << player1 << " wins!!" << endl;
			else cout << endl << player2 << " wins!!" << endl;
		}
	}
}

int C4Board::didWin(char uPlay, int userCol) {
	int count4[4] = {0},	// array keeping track of how many discs are in a row, relative to the disc just played. array follows as such: [NW-SE diagonal, W-E, SW-NE diagonal, S-N]
		// colShift and rowShift are used to check how many discs the player has in a row. Both colShift and rowShift start as zero, meaning that the first disc checked is the one just played. It is true that this disc will have the same value as the current user whose turn it is, so the count4 will equal 1. Then, depending on the direction that is being checked, colShift and/or rowShift will be increased or decreased by 1. This will consequentally check an adjacent disc, to see if it belongs to the current user. If it does, then the count will increase by one.
		colShift=0,
		rowShift=0,
		userRow=(board[userCol].getNumDisc())-1,	// grabs the row in which a disc was just played(subtracts 1 to match array indexing)
		i,		// for loop counter
		isWin=0;	// boolean variable. isWin=1 if four discs in a row are found.
	for(i=0;i<=6;i++){	// 0-6 correspond to 7 different directions around the disc just played. Note: there is not an 8th because there can be no disc directly above the one just played
		// set colShift and rowShift =0 to ensure first disc checked is the one just played
		colShift=0;
		rowShift=0;
		while(userCol+colShift>=0 && userCol+colShift<=6 && userRow+rowShift>=0 && userRow+rowShift<=5){	// while the location being checked is still within the bounds of the board...
			if(uPlay == board[userCol+colShift].getDisc(userRow+rowShift)){	//if the disc being checked belongs to the user whos turn it currently is...
				if(i<=3){
					count4[i]++;
					if(count4[i]>=4){	// if four discs in a row are found...
						isWin=1;
						break;
					}
				// all discs found for i=4,5,6 are added to count4[0,1,2] respectively. This is because they correspond to matching directions. (eg. i=0 checks the northwest direction, while i=4 checks the southeast direction
				}else{
					if(colShift==0 && rowShift==0) count4[i-4]--;	// subtracts one from the count of count4[1,2,3] when i=4,5,6 because the current disc just played has already been accounted for from when i=0,1,2
					count4[i-4]++;
					if(count4[i-4]>=4){	// if four discs in a row are found...
						isWin=1;
						break;
					}
				}
				switch(i){
					// Shifts the column and/or row currently being checked, corresponding to the direction in which discs are currently being checked
					case 0:	// Northwest - top left
						colShift-=1;
						rowShift+=1;
						break;
					case 1: // West
						colShift-=1;
						break;
					case 2:	// Southwest - bottom left
						colShift-=1;
						rowShift-=1;
						break;
					case 3:	// South
						rowShift-=1;
						break;
					case 4:	// Southeast - bottom right
						colShift+=1;
						rowShift-=1;
						break;
					case 5:	// East
						colShift+=1;
						break;
					case 6:	// Northeast - top right
						colShift+=1;
						rowShift+=1;
						break;
					default:
						break;
				}
				
			}else{
				break;	// disc checked does not belong to the current player->exit loop and check next direction
			}
		}
	}
	return(isWin);	// return if the current player won or not
}

void C4Board::comp() {
	int userCol=0,		// column the user chooses to play disc in
		userTurn=0,	// counts up total number of turns
		miss=0,		// used to determin if user plays piece out of bounds
		isWin=0;	// boolean variable. true if a player wins the game
	string player1, player2;// users names
	// input of users' names
	cout << "You have selected one player mode!\nPlease enter your name: ";
	cin >> player1;
	player2 = "Computer";
	cout << "Here are your game piece assignments..." << endl << endl << player1 << ": X" << endl << player2 << ": O" << endl << endl;
	// game instructions printed
	cout << "To play your piece when it is your turn, simply enter the column number desired when prompted.\nPlease note: you may exit at any time by entering the value: -1\n\nLet's begin!" << endl << endl;	
	display();	// print empty board

	while(userCol != -1){
		userTurn++;		// increment total turns each time a disc is played
		cout << "Which column would you like to play your disc?" << endl;
		miss=0;			// reset miss to 0
		if(userTurn%2 == 1) {	// true if it is player 1's turn
			do {
				if(miss>0) {cout << "Error. Please enter a number [1,7]\n";}	
				miss++;
				cout << player1 << ": ";		//prompt user for disc placement
				(cin >> userCol);			// grab the user column
			}while((userCol<1 || userCol>7)&& userCol!=-1);	//checks to make sure the disc is played within bounds of board
		}else{
			userCol = (rand()%7)+1;
		}
		// If the user chooses to quit, display message and exit game(ie. exit while loop)
		if(userCol==-1){
			cout << "Thank you for playing!" << endl;
			break;
		}
		userCol-=1;	// Now that we have checked if user entered -1, change userCol so that it corresponds to the location in the array of columns
		// If the user plays in a full column, display error message, and then subtract a turn from total turns so that the same player may go again
		if(board[userCol].isFull()) {
			cout << "Column is full. Please try again." << endl;
			userTurn--;
		// If the user played in a valid column, add the disc to the board and check to see if they won
		}else{
			if(userTurn%2 == 1) {
				board[userCol].addDisc('X');
				isWin=didWin('X',userCol);
			}else{
				board[userCol].addDisc('O');
				isWin=didWin('O',userCol);
			}
			system("clear");	// clear the screen for clean display
			cout << player1 << ": X\n" << player2 << ": O\n\n";	// display user discs as a reminder
		}
		display();	// display the board
		// If the user wins, end the game(ie. exit the whil loop) and display a message declaring them as the winner!
		if(isWin){
			userCol=-1;
			if(userTurn%2 == 1) cout << endl << player1 << " wins!!" << endl;
			else cout << endl << player2 << " wins!!" << endl;
		}
	}
}
