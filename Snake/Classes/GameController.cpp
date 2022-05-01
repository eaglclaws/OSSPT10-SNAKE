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

	recordRank;
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


