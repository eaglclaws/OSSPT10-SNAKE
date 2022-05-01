#include "GameController.h"
#include "Game.h"
#include "Board.h"
#include <string>
#include <fstream>


GameController* GameController::instance = nullptr;
bool GameController::isCreated = false;

void GameController::clicked(bool isLoad) {
	instance = getInstance();
	instance->isLoadClicked = isLoad; //load 클릭 시 true | start 클릭 시 false
}

GameController* GameController::getInstance() {
	if (!isCreated) {
		instance = new GameController();
		isCreated = true;
	}
	return instance;
}


void GameController::resetGame() {
	this->game->init();
    game->place_apple(25, 5);
	this->game->play();
}


int** GameController::loadBoard() {
	int** board = new int*[BOARD_HEIGHT];
	for (int i = 0; i < BOARD_HEIGHT; i++)
		board[i] = new int[BOARD_WIDTH];

	//load 
	string data;

	ifstream fin;
	fin.open("board.txt");
	getline(fin, data);
    fin.close();

	int token, size = data.size();
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			token = data.find(",");
			board[i][j] = stoi(data.substr(0, token));
			data = data.substr(token + 1, size - token - 1);
		}
	}

	return board;
}


vector<pair<int, int>>* GameController::loadSnake() {
	vector<pair<int, int>>* snake = new vector<pair<int, int>>;
	
	//get snake string;
	string data;

	ifstream fin;
	fin.open("snake.txt");
	getline(fin, data);
    fin.close();

	int ftoken, stoken, size = data.size();
	while (data.find(";") != string::npos) {
		ftoken = data.find(";");
		stoken = data.find(",");

		snake->push_back(pair<int, int>(stoi(data.substr(0, stoken)), stoi(data.substr(stoken + 1, ftoken - stoken - 1))));

		data = data.substr(ftoken + 1, size - ftoken - 1);
	}

    return snake;
}

int GameController::loadDirection() {
	string data;

	ifstream fin;
	fin.open("direction.txt");
	getline(fin, data);
    fin.close();

	return stoi(data);
}

void GameController::saveBoard(int** board) {
	string data;
	
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			data = data + to_string(board[i][j]) + ",";

	//save!
	ofstream fout;
	fout.open("board.txt");
=======
#include <stdio.h>
#include <algorithm>
#include <fstream>

using namespace std;

int GameController::getScore() {
	return this->score;
}

void GameController::setScore(int score) {
	this->score = score;
}

void GameController::addUser(string user) {
	pair<int, string> p = make_pair(this->score, user);
	this->ranking.push_back(p);
	sort(this->ranking.begin(), this->ranking.end(), greater<>());

	while (this->ranking.size() > 10) {
		this->ranking.pop_back();
	}

	recordRank();
}

void GameController::recordRank() {
	string data;
	for (int i = 0; i < this->ranking.size(); i++) {
		data = data + to_string(this->ranking[i].first) + ',' + this->ranking[i].second;
	}

	ofstream fout;
	fout.open("ranking.txt");
>>>>>>> origin/gamecontroller
	fout << data;
	fout.close();
}

<<<<<<< HEAD
void GameController::saveSnake(vector<pair<int, int>>* snake) {
	string data = "";
	for (int i = 0; i < snake->size(); i++) {
		data = data + to_string(snake->at(i).first) + "," + to_string(snake->at(i).second) + ";";
	}
	//save!
	ofstream fout;
	fout.open("snake.txt");
	fout << data;
	fout.close();
}

void GameController::saveDirection(int dir) {
	ofstream fout;
	fout.open("direction.txt");
	fout << to_string(dir);
	fout.close();
}

void GameController::setGame(Game* gameInstance) {
	this->game = gameInstance;
}

void GameController::saveGame() {
    printf("%p\n", game);
	int ** board = game->export_board();
	vector<pair<int, int>>* snake = game->export_snake();
	int dir = game->export_dir();

	this->saveBoard(board);
	this->saveSnake(snake);
	this->saveDirection(dir);
}

void GameController::gamePlay() {
	this->game->play();
}

vector<pair<int, string>> GameController::getRocordedRank() {
	string readLine;
	vector<pair<int, string>> data;

	ifstream fin;
	fin.open("ranking.txt");

	int token = 0;
	int size = 0;

	int i = 0;

	while (fin.peek() != EOF) {
		getline(fin, readLine);
		token, size = readLine.size();
		token = readLine.find(",");

		data[i].first = stoi(readLine.substr(0, token));
		data[i].second = readLine.substr(token + 1, size - token - 1);
	}

	return data;
}
