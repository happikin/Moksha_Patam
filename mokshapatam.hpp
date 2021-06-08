#include<iostream>
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

class Player {
    std::string name;
    int currentLocation,maxLocation;
    bool endReached;
    
    public:
        Player(std::string name) {
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
        std::string getName() {
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
            if(steps <= currentLocation)
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
        std::string *playerNames;
        bool ladderStart,snakeStart;
        int ladderSize,snakeSize;
    public:
        Box() {
            playerCount = _ZERO;
            playerNames = new std::string[playerCount];
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
    private:
        Player *playerList;
        int playerCount;
        std::string playerName;
        Sizes boardSize;
    // will contain methods to handle the basic setups for a game
    public:
        GameHandler() {
            chooseBoardSize();   
            registerPlayers();
        }
        Player* getGamePlayers() {
            return playerList;
        }
        int getPlayerCount() {
            return playerCount;
        }
        void registerPlayers() {
            std::cout<<"How many players wish to play Moksha Patam? ";
            std::cin>>playerCount;
            playerList = new Player[playerCount];
            int i = 0;
            while(i < playerCount) {
                std::cout<<"Enter your game name: ";
                std::cin>>playerName;
                playerList[i++] = {playerName};
            }
        }
        void chooseBoardSize() {
            std::cout<<"- - - - CHOOSE BOARD SIZE - - - -"<<std::endl;
            std::cout<<"Enter one of the following option numbers: "<<std::endl;
            std::cout<<"1. 8 X 8"<<std::endl;
            std::cout<<"2. 10 X 10"<<std::endl;
            std::cout<<"3. 12 X 12"<<std::endl;
            int option;
            std::cin>>option;
            switch(option) {
                case 1:
                    boardSize = _8X8;
                    break;
                case 2:
                    boardSize = _10X10;
                    break;
                case 3:
                    boardSize = _12X12;
                    break;
                default:
                    exit(1);
                    break;
            }
        }
        Sizes getBoardSize() {
            return boardSize;
        }
};