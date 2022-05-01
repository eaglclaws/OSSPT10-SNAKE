#include "GameController.h"
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
	fout << data;
	fout.close();
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