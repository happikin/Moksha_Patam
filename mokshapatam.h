#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<Thread>
enum PlayerCount {
	_ZERO = 0,
	_TWO = 2,
	_THREE = 3,
	_FOUR = 4
};
enum Sizes {
	_NULL = 0,
	_8X8 = 64,
	_10X10 = 100,
	_12X12 = 144
};
class Dice {
public:
	static int roll() {
		return rand() % 6 + 1;
	}
};
class Player {
	std::string name;
	int currentLocation, maxLocation;
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
		if (currentLocation != maxLocation)
			currentLocation += steps;
		if (currentLocation == maxLocation) {
			endReached = true;
		}
	}
	void moveBackBy(int steps) {
		if (steps <= currentLocation)
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
	bool ladderStart, snakeStart;
	int ladderSize, snakeSize;
public:
	Box() {
		playerCount = _ZERO;
		playerNames = new std::string[playerCount];
	}
	void init() {

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
		while (i < boardSize) {
			i++;
		}
		return i;
	}
	void allotPlayers(Player players[], int count) {
		playerList = players;
		playerCount = count;
		for (int i = 0; i < this->playerCount; i++)
			playerList[i].setMaxLocation(boardSize);
	}
	Player* getPlayer(int playerIndex) {
		return &playerList[playerIndex];
	}
	void reset() {
		playerList = nullptr;
		boardBoxes = nullptr;
	}
	/*void setup(vector<Ladder> ladder_vect,vector<Snake> snake_vect) {

	}*/
};
class Ladder {
public:
	int start;
	int end;
	Ladder(int s, int e)
	{
		start = s; end = e;
	}
	Ladder() {}
};
class Snake {
public:
	int start;
	int end;
};
class GameHandler {
private:
	std::vector<Ladder> ladder_vect;
	std::vector<Snake> snake_vect;
	std::string inGameMessage;
	Player *playerList;
	int playerCount;
	std::string playerName;
	Sizes boardSize;
	std::string registerPlayers() {
		std::cout << "How many players wish to play Moksha Patam? ";
		std::cin >> playerCount;
		if (playerCount <= 1) {
			inGameMessage = "ERROR:Invalid number of players \n";
			return "ERROR:Invalid number of players";
		}
		playerList = new Player[playerCount];
		int i = 0;
		while (i < playerCount) {
			std::cout << "Enter your game name: ";
			std::cin>>playerName;
			playerList[i++] = { playerName };
		}
		return "MESSAGE: Players registered \n";
	}
	int* splitInTwoNums(std::string str, char separator) {
		std::stringstream ss;
		int *nums = new int[2];
		int i = 0, j = 0;
		while (str[i] != separator) i++;
		ss << str.substr(0, i);
		ss >> nums[0];
		j = i;
		ss.clear();
		int len = str.length(), b = 0;
		ss << str.substr(j + 1, len);
		ss >> nums[1];
		return nums;
	}
	void chooseBoardSize() {
		std::cout << "- - - - CHOOSE BOARD SIZE - - - -" << std::endl;
		std::cout << "Enter one of the following option numbers: " << std::endl;
		std::cout << "1. 8 X 8" << std::endl;
		std::cout << "2. 10 X 10" << std::endl;
		std::cout << "3. 12 X 12" << std::endl;
		int option;
		std::cin >> option;
		switch (option) {
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
	// will contain methods to handle the basic setups for a game
public:
	GameHandler() {
			chooseBoardSize();
			this->inGameMessage = registerPlayers();
	}
	Player* getGamePlayers() {
		return playerList;
	}
	int getPlayerCount() {
		return playerCount;
	}
	Sizes getBoardSize() {
		return boardSize;
	}
	std::string getInGameMessage() {
		return inGameMessage;
	}
	void prepBoardData() {
		std::thread t_ladder;
		std::thread t_snake;
	}
	void prepLadderVect() {
		std::stringstream ss;
		std::ifstream _10X10Ladder;
		_10X10Ladder.open("D:\\Practice C++ Coding\\CPP\\Moksha_Patam\\BoardSetupData\\_10X10\\_10X10LADDERS.txt", std::ios::in);
		if (!_10X10Ladder) std::cerr << "COULD NOT OPEN FILE" << std::endl;
		if (_10X10Ladder.is_open()) {
			std::cout << "Ladder File is open" << std::endl;
			std::string dat;
			int *num;
			int c = 0;
			while (getline(_10X10Ladder, dat)) {
				//std::cout << " - - - - - " << c + 1 << "Ladder" << std::endl;
				num = splitInTwoNums(dat, ',');
				Ladder l1(num[0], num[1]);
				ladder_vect.push_back(l1);
				/*cout << ladder_vect[c].start << endl;
				cout << ladder_vect[c].end << endl;*/
				c++;
			}
			std::cout << "Loading Ladder data complete!" << std::endl;
		}
		else
		{
			std::cout << "Not opened";
		}
	}
	void prepSnakeVect() {
		std::stringstream ss;
		std::ifstream _10X10Ladder;
		_10X10Ladder.open("D:\\Practice C++ Coding\\CPP\\Moksha_Patam\\BoardSetupData\\_10X10\\_10X10SNAKES.txt", std::ios::in);
		if (!_10X10Ladder) std::cerr << "COULD NOT OPEN FILE" << std::endl;
		if (_10X10Ladder.is_open()) {
			std::cout << "Snake File is open" << std::endl;
			std::string dat;
			int *num;
			int c = 0;
			while (getline(_10X10Ladder, dat)) {
				//std::cout << " - - - - - " << c + 1 << "Ladder" << std::endl;
				num = splitInTwoNums(dat, ',');
				Ladder l1(num[0], num[1]);
				ladder_vect.push_back(l1);
				/*cout << ladder_vect[c].start << endl;
				cout << ladder_vect[c].end << endl;*/
				c++;
			}
			std::cout << "Loading Snake data complete!" << std::endl;
		}
		else
		{
			std::cout << "Not opened";
		}
	}
	std::vector<Ladder> getLadders() {
		return ladder_vect;
	}
	std::vector<Snake> getSnakes() {
		return snake_vect;
	}
};

class GameData : public GameHandler {
	std::vector<Ladder>::iterator ladderIt;
	std::vector<Snake>::iterator snakeIt;
	std::vector<Ladder> ladder_vect;
	std::vector<Snake> snake_vect;
public:
	void showLadderData() {
		std::cout << " - - LADDER PAIR VALUES [START,END] - - " << std::endl;
		ladder_vect = getLadders();
		ladderIt = ladder_vect.begin();
		while (ladderIt != ladder_vect.end()) {
			std::cout << ladderIt->start << "," << ladderIt->end << std::endl;
			ladderIt++;
		}
	}
	void showSnakeData() {
		std::cout << " - - SNAKE PAIR VALUES [START,END] - - " << std::endl;
		snake_vect = getSnakes();
		snakeIt = snake_vect.begin();
		while (snakeIt != snake_vect.end()) {
			std::cout << snakeIt->start << "," << snakeIt->end << std::endl;
			snakeIt++;
		}
	}
};