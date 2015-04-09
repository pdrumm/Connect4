/*
 * Patrick Drumm
 * cse20212, lab1
 * Main is the driver for connect4.cpp! This program includes 2 header files(C4Board.h and C4Col.h) in order to utilize classes to create a fun connect 4 game. There are two game modes: 1 player and 2 player.
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "C4Board.h"

using namespace std;

int main() {
	int userMode;
	system("clear");
	C4Board c4;	// instantiate an instance of a C4Board object
	cout << "Welcome to Connect 4!\nTo play against the computer, please enter: 1\nFor two player mode, please enter: 2\nMode: ";
	cin >> userMode;	// user chooses 1(=one player) or 2(=two player)
	while(userMode!=1 && userMode!=2){
		cout << "Error, that is not a valid option.\nPlease enter an integer value, 1 or 2: ";
		cin >> userMode;
	}
	if(userMode==2)
		c4.play();	// play two player game!
	else if(userMode==1)
		c4.comp();	// play vs. the computer!
	else
		cout << "Error. Input was not valid." << endl;
}
