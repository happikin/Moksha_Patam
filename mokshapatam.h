#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<thread>
#include<time.h>
enum class PlayerCount {
	_ZERO = 0,
	_TWO = 2,
	_THREE = 3,
	_FOUR = 4
};
enum class Sizes {
	_NULL = 0,
	_8X8 = 64,
	_10X10 = 100,
	_12X12 = 144
};
class Dice {
public:
	static int roll() {
		srand(time(0));
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
		if (steps >=0 && steps <= maxLocation) {
			if (currentLocation != maxLocation)
				currentLocation += steps;
			if (currentLocation == maxLocation) {
				endReached = true;
			}
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
	Snake(int s, int e) {
		start = s; end = e;
	}
	Snake() {}
};
class Box {
private:
	PlayerCount playerCount;
	std::string *playerNames;
	bool ladderStart, snakeStart;
	int ladderEnd, snakeEnd;
public:
	Box() {
		ladderEnd = 0;
		snakeEnd = 0;
		ladderStart = false;
		snakeStart = false;
		playerCount = PlayerCount::_ZERO;
		playerNames = new std::string[int(playerCount)];
	}
	void allotLadder(int end) {
		ladderStart = true;
		ladderEnd = end;
	}
	void allotSnake(int end) {
		snakeStart = true;
		snakeEnd = end;
	}
	int getLadderEnd() {
		return ladderEnd;
	}
	int getSnakeEnd() {
		return snakeEnd;
	}
	bool hasSnake() { return snakeStart; }
	bool hasLadder() { return ladderStart; }
};

class Board {
private:
	Player *playerList;
	int playerCount;
	Sizes boardSize;
	Box *boardBoxes;
public:
	Board() {
		boardSize = Sizes::_NULL;
		boardBoxes = new Box[int(boardSize)];
		playerCount = 0;
		playerList = nullptr;
	}
	Board(Sizes size) {
		boardSize = size;
		boardBoxes = new Box[int(boardSize)];
		playerCount = 0;
		playerList = nullptr;
	}
	int getSize() {
		int i = 0;
		while (i < int(boardSize)) {
			i++;
		}
		return i;
	}
	void allotPlayers(Player players[], int count) {
		playerList = players;
		playerCount = count;
		for (int i = 0; i < this->playerCount; i++)
			playerList[i].setMaxLocation(int(boardSize));
	}
	Player* getPlayer(int playerIndex) {
		return &playerList[playerIndex];
	}
	void reset() {
		playerList = nullptr;
		boardBoxes = nullptr;
	}
	void attachLadders(std::vector<Ladder> ladder_vect) {
		std::cout << "INSIDE ATTACH LADDER METHOD" << std::endl;
		int lCount = ladder_vect.size();
		for (int i = 0; i < lCount; i++) {
			boardBoxes[ladder_vect[i].start - 1].allotLadder(ladder_vect[i].end - 1);
		}
		std::cout << "All ladders attached" << std::endl;
	}
	void attachSnakes(std::vector<Snake> snake_vect) {
		int sCount = snake_vect.size();
		for (int i = 0; i < sCount; i++) {
			boardBoxes[snake_vect[i].start - 1].allotSnake(snake_vect[i].end - 1);
		}
		std::cout << "All snakes attached" << std::endl;
	}
	void setup(std::vector<Ladder> ladder_vect, std::vector<Snake> snake_vect) {
		if (ladder_vect.size() != 0 && snake_vect.size() != 0) {
			attachLadders(ladder_vect);
			attachSnakes(snake_vect);
		}
		else
		{
			std::cout << "Ladders & Snakes failed to prep. Please Try again." << std::endl;
		}
	}
	Box* getBoard() {
		return boardBoxes;
	}
	int getPlayerCount() {
		return playerCount;
	}
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
	std::string boardDataFolderName;
	std::string choice = "start";
	std::string Choices[3] = {"start","reset","exit"};
	
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
			std::cin >> playerName;
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
			boardSize = Sizes::_8X8;
			boardDataFolderName = "_8X8";
			break;
		case 2:
			boardSize = Sizes::_10X10;
			boardDataFolderName = "_10X10";
			break;
		case 3:
			boardSize = Sizes::_12X12;
			boardDataFolderName = "_12X12";
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
			this->prepLadderVect();
			this->prepSnakeVect();
	}
	void prepLadderVect() {
		
		std::stringstream ss;
		std::ifstream ladderFile;
		std::string fileLoc = "D:\\Practice C++ Coding\\CPP\\Moksha_Patam\\BoardSetupData\\";
		fileLoc.append(boardDataFolderName);
		fileLoc.append("\\LADDERS.txt");
		ladderFile.open(fileLoc, std::ios::in);
		if (!ladderFile) {
			std::cerr << "COULD NOT OPEN FILE" << std::endl;
			exit(1);
		}
		if (ladderFile.is_open()) {
			std::cout << "Ladder File is open" << std::endl;
			std::string dat;
			int *num;
			int c = 0;
			while (getline(ladderFile, dat)) {
				num = splitInTwoNums(dat, ',');
				Ladder l1(num[0], num[1]);
				ladder_vect.push_back(l1);
				c++;
			}
			std::cout << "Loading Ladder data complete!" << std::endl;
		}
		else
		{
			std::cout << "Not opened";
		}
		ladderFile.close();
	}
	void prepSnakeVect() {
		std::stringstream ss;
		std::ifstream snakeFile;
		std::string fileLoc = "D:\\Practice C++ Coding\\CPP\\Moksha_Patam\\BoardSetupData\\";
		fileLoc.append(boardDataFolderName);
		fileLoc.append("\\SNAKES.txt");
		snakeFile.open(fileLoc, std::ios::in);
		if (!snakeFile) {
			std::cerr << "COULD NOT OPEN FILE" << std::endl;
			exit(1);
		}
		if (snakeFile.is_open()) {
			std::cout << "Snake File is open" << std::endl;
			std::string dat;
			int *num;
			int c = 0;
			while (getline(snakeFile, dat)) {
				num = splitInTwoNums(dat, ',');
				Snake s1(num[0], num[1]);
				snake_vect.push_back(s1);
				c++;
			}
			std::cout << "Loading Snake data complete!" << std::endl;
		}
		else
		{
			std::cout << "Not opened";
		}
		snakeFile.close();
	}
	std::vector<Ladder> getLadders() {
		return ladder_vect;
	}
	std::vector<Snake> getSnakes() {
		return snake_vect;
	}
	bool runGame(Board gameBoard);
	void displayPlayers(Board gameBoard) {
		for (int i = 0; i < gameBoard.getPlayerCount(); i++) {
			std::cout << "Player " << i+1 << ": " << gameBoard.getPlayer(i)->getName() << std::endl;
		}
	}
	void toss() {
		std::cout<<"choose [even / odd]"<<std::endl;
		std::string ch; 
		std::cin >> ch;
		Dice dice;
		int rollResult = dice.roll() % 6 + 1;
		if (rollResult == 2 || rollResult == 4 || rollResult == 6) {
			return;
		}
	}
};

bool GameHandler::runGame(Board gameBoard) {
	Dice dice;
	system("CLS");
	std::cout << " - - Welcome to Moksha Patam an ancient Indian board game which gained popularity by the name Snakes & Ladders! - - " << std::endl;
	displayPlayers(gameBoard);
	//this entire function will oscillate sequentially between 'turns'
	std::string choice = "start";
	while (choice != "exit")
	{
		int i = 0;
		for (; i < gameBoard.getPlayerCount() ; i++) {
			std::cout << "Turn of " << gameBoard.getPlayer(i)->getName() << std::endl;
			std::string ch;
			std::cout << "type \"roll\" to roll the dice : else next players turn will come up! " << std::endl;
			std::cin >> ch;
			if (ch == "roll") {
				int rollResult = dice.roll();
				std::cout << "Die roll result: " << rollResult << std::endl;
				gameBoard.getPlayer(i)->moveAheadBy(rollResult);
				std::cout << gameBoard.getPlayer(i)->getName() << " Moved ahead by " << rollResult << " steps" << std::endl;
				if (gameBoard.getBoard()[gameBoard.getPlayer(i)->getCurrentLocation()].hasLadder()) {
					std::cout << "Hurray!! Your current location has a ladder! lets Climb ;-)) " << std::endl;
					gameBoard.getPlayer(i)->moveAheadBy(gameBoard.getBoard()[gameBoard.getPlayer(i)->getCurrentLocation()].getLadderEnd());
					std::cout << "New location of " << gameBoard.getPlayer(i)->getName() << "is : " << gameBoard.getPlayer(i)->getCurrentLocation() << std::endl;
				}
				else if (gameBoard.getBoard()[gameBoard.getPlayer(i)->getCurrentLocation()].hasSnake()) {
					std::cout << "Oopsiee!! Your current location has a snake! Here we go down :-(( " << std::endl;
					gameBoard.getPlayer(i)->moveBackBy(gameBoard.getBoard()[gameBoard.getPlayer(i)->getCurrentLocation()].getSnakeEnd());
					std::cout << "New location of " << gameBoard.getPlayer(i)->getName() << "is : " << gameBoard.getPlayer(i)->getCurrentLocation() << std::endl;
				}
			}
			else
			{
				std::cout << "Turn of next player will come up now!" << std::endl;
			}
			std::cout << "Please type \"exit\" if you wish to exit the game" << std::endl;
			std::cin >> choice;
			if (choice == "exit") {
				return true;
			}
		}
	}

	return true;
}


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