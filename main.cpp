/**
 * Moksha Pata is an ancient but a very famous board game even in todays modern world.
 * This game has its origin from India and is more popularly called as 
 * Snakes and Ladders or Chutes and Ladders
 *
 */

#include<iostream>
using namespace std;
enum PlayerCount {
    _ZERO=0,
    _TWO = 2,
    _THREE = 3,
    _FOUR = 4
};
enum Sizes {
    _NULL=0,
    _8X8=64,
    _10X10=100,
    _12X12=144
};
class Box {
    private:
        PlayerCount playerCount;
        string *playerNames;
        bool ladderStart,snakeStart;
        int ladderSize,snakeSize;
    public:
    Box() {
        playerCount = _ZERO;
        playerNames = new string[playerCount];
    }
    Box() {
        
    }
};
class Board {
    private:
        Sizes boardSize;
        Box *boardBoxes;
    public:
        Board() {
            boardSize = _NULL;
            boardBoxes = new Box[boardSize];
            boardBoxes[0];
        }
        Board(Sizes size) {
            boardSize = size;
            boardBoxes = new Box[boardSize];
        }
        int getSize() {
            int i = 0;
            while(i < boardSize) {
                i++;
            }
            return i;
        }

};


int main() {
    Board mokshaPatam(_8X8);
    cout<<mokshaPatam.getSize();
}