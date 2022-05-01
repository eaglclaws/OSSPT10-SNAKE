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

bool compare(const pair<int, string>& a, const pair<int, string>& b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	return a.first > b.first;
}

void GameController::addUser(string user) {
	ranking = getRocordedRank();

	pair<int, string> p = make_pair(this->score, user);
	this->ranking.push_back(p);
	sort(this->ranking.begin(), this->ranking.end(), compare);

	while (this->ranking.size() > 10) {
		this->ranking.pop_back();
	}

	recordRank();
}

void GameController::recordRank() {
	string data;
	for (int i = 0; i < this->ranking.size(); i++) {
		data = data + to_string(this->ranking[i].first) + ',' + this->ranking[i].second + '\n';
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
	int first = 0;;
	string second;

	while (getline(fin, readLine)) {

		token, size = readLine.size();
		token = readLine.find(",");

		first = stoi(readLine.substr(0, token));
		second = readLine.substr(token + 1, size - token - 1);

		data.push_back(make_pair(first, second));
		i++;
	}

	fin.close();
	return data;
}