#include "GameController.h"
#include <stdio.h>
#include <algorithm>

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
	sort(ranking.begin(), ranking.end(), greater<>());

	while (ranking.size() > 10) {
		ranking.pop_back();
	}
}
