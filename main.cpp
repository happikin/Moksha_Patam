/**
 * Moksha Pata is an ancient but a very famous board game even in todays modern world.
 * This game has its origin from India and is more popularly called as
 * Snakes and Ladders or Chutes and Ladders
 *
 */

#include<iostream>
#include "mokshapatam.h"
using namespace std;

int main() {
	GameHandler handler;
	Board mokshaPatam(handler.getBoardSize());  // - board created without any ladders and snakes over it
	mokshaPatam.allotPlayers(handler.getGamePlayers(), handler.getPlayerCount());
	cout << handler.getInGameMessage();
	handler.prepBoardData();
	mokshaPatam.setup(handler.getLadders(), handler.getSnakes());
	Box *board = mokshaPatam.getBoard();
	// now we have to implement game play logic
	/*
	- we must have a dice to roll
	- the players must be at location 0(0 means 1st box in the boardBox array)
	*/
	string choice = "restart";
	while (choice == "restart") {
		choice = "exit";
		bool state = handler.runGame(mokshaPatam);
		if (state)
			cout << "Thank you for playing the game" << endl;
		else
		{
			cout << "Type \"restart\" to play the game again: else type \"exit\" to end the game" << endl;
			cin >> choice;
		}
	}
	return 0;
}