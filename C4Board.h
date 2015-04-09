/*
 * Patrick Drumm
 * cse20212, lab1
 * Note: Functions added:
 * 	didWin() - determines if the current player has won on their most recent move.
 * 	comp() - very similar structure to play(), but is edited so that a single user can play the computer
 */
#ifndef C4BOARD_h
#define C4BOARD_h
#include "C4Col.h"

class C4Board {
	public:
		C4Board();	// constructor
		~C4Board();	// deconstructor
		void display();	// displays the current board in simple text
		void play();	// allows two players to play the game
		void comp();	// one player mode vs. computer
	private:
		int numCol;	// number of columns
		C4Col *board;
		int didWin(char,int);
};

#endif
