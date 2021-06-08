/**
 * Moksha Pata is an ancient but a very famous board game even in todays modern world.
 * This game has its origin from India and is more popularly called as 
 * Snakes and Ladders or Chutes and Ladders
 *
 */

#include<iostream>
#include<stdlib.h>
#include "mokshapatam.hpp"
using namespace std;


class Player {
    string name;
    int currentLocation,maxLocation;
    bool endReached;
    
    public:
        Player(string name) {
            this->name = name;
            currentLocation = 0;
            maxLocation = 0;
            endReached = false;
        }
        Player() {
            currentLocation = 0;
            maxLocation = 0;
            endReached = false;
        }
        string getName() {
            return name;
        }
        void moveAheadBy(int steps) {
            if(currentLocation != maxLocation)
                currentLocation += steps;
                if(currentLocation == maxLocation) {
                    endReached = true;
                } 
        }
        void moveBackBy(int steps) {
            if(currentLocation!=0)
                currentLocation -= steps;
        }
        int getCurrentLocation() {
            return currentLocation;
        }
        void setMaxLocation(int max) {
            maxLocation = max;
        }
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
        void init() {

        }
};

class Dice {
    public:
        static int roll() {
            return rand()%6+1;
        }
};

class Board {
    private:
        Player *playerList;
        int playerCount;
        Sizes boardSize;
        Box *boardBoxes;
    public:
        Board() {
            boardSize = _NULL;
            boardBoxes = new Box[boardSize];
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
        void init() {

        }
        void allotPlayers(Player players[], int count) {
            playerList = players;
            playerCount = count;
            for(int i=0 ; i<this->playerCount ; i++)
                playerList[i].setMaxLocation(boardSize);
        }
        Player* getPlayer(int playerIndex) {
            return &playerList[playerIndex];
        }
        void reset() {
            playerList = nullptr;
            boardBoxes = nullptr;
        }
};
class GameHandler {

};
int main() {
    Board mokshaPatam(_12X12);
    // - board of 100 blocks has been created in memeory
    // - without any ladders and snakes over it
    Dice dice1;
    cout<<"How many players wish to play Moksha Patam? ";
    int playerCount;
    cin>>playerCount;
    Player *playerList = new Player[playerCount];
    int i = 0;
    string playerName;
    while(i < playerCount) {
        cout<<"Enter your game name: ";
        cin>>playerName;
        playerList[i++] = {playerName};
    }
    // - two players have been made
    mokshaPatam.allotPlayers(playerList,playerCount);
    cout<<mokshaPatam.getPlayer(1)->getName()<<endl;

    mokshaPatam.getPlayer(0)->moveAheadBy(10);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    mokshaPatam.getPlayer(0)->moveAheadBy(90);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    mokshaPatam.getPlayer(0)->moveAheadBy(1);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    mokshaPatam.getPlayer(0)->moveAheadBy(12);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    mokshaPatam.getPlayer(0)->moveAheadBy(31);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    mokshaPatam.getPlayer(0)->moveAheadBy(1);
    cout<<mokshaPatam.getPlayer(0)->getCurrentLocation()<<endl;
    return 0;
}