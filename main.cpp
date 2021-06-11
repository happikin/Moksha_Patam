/**
 * Moksha Pata is an ancient but a very famous board game even in todays modern world.
 * This game has its origin from India and is more popularly called as
 * Snakes and Ladders or Chutes and Ladders
 *
 */

#include<iostream>
#include "ll.h"
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
	
	cout << "Ladder End: " << board[7].getLadderEnd() << endl;
	cout << "Snake End: " << board[97].getSnakeEnd() << endl;
	if (board[97].hasSnake()) {
		cout << "HAS SNAKE" << endl;
	}

	return 0;
}