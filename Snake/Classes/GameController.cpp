#include "GameController.h"
#include "Game.h"
#include <string>
#include <fstream>


GameController* GameController::instance = nullptr;
bool GameController::isCreated = false;

void GameController::clicked(bool isLoad) {
	instance = getInstance();
	isLoadClicked = isLoad; //load 클릭 시 true | start 클릭 시 false
}

GameController* GameController::getInstance() {
	if (!isCreated) {
		instance = new GameController();
		isCreated = true;
	}
	return instance;
}


void GameController::resetGame() {
	this->game->game_init();
	this->game->game_play();
}


int** GameController::loadBoard() {
	int** board = new int*[40];
	for (int i = 0; i < 40; i++)
		board[i] = new int[40];

	//load 
	string data;

	ifstream fin;
	fin.open("board.txt");
	getline(fin, data);


	int token, size = data.size();
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
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

	int ftoken, stoken, size = data.size();
	while (data.find(";") != string::npos) {
		ftoken = data.find(";");
		stoken = data.find(",");

		snake->push_back(pair<int, int>(stoi(data.substr(0, stoken)), stoi(data.substr(stoken + 1, ftoken - stoken - 1))));

		data = data.substr(ftoken + 1, size - ftoken - 1);
	}
}

int GameController::loadDirection() {
	string data;

	ifstream fin;
	fin.open("direction.txt");
	getline(fin, data);

	return stoi(data);
}

void GameController::saveBoard(int** board) {
	string data;
	
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
			data = data + to_string(board[i][j]) + ",";

	//save!
	ofstream fout;
	fout.open("board.txt");
	fout << data;
	fout.close();
}

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
	int ** board = game->export_board();
	vector<pair<int, int>>* snake = export_snake();
	int dir = export_dir();

	this->saveBoard(board);
	this->saveSnake(snake);
	this->saveDirection(dir);
}