/*
 * Patrick Drumm
 * cse20212, lab1
 * Note: I added a function - getNumDisc() - in which I use to determine the row which the last disc was played. I use this to find if the user has won on the last move or not
 */
#ifndef C4COL_H
#define C4COL_H

class C4Col {
	public:
		C4Col();		// constructor
		int isFull();		// determines if the column is full
		char getDisc(int discX);	// returns the requested element of the private character array
		int getMaxDiscs();	// returns the maximum number of discs
		void addDisc(char newDisc);	// adds the character representing a disc to the next open slot in the Disc array
		int getNumDisc();	// returns the number of discs in the column
		C4Col operator+=(char addedDisc);
	private:
		int numDisc;
		int maxDisc;
		char playerDiscs[6];
};

#endif
