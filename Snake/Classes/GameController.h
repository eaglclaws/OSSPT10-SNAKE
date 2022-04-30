#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class GameController {

private:
	//���� �ֱ� score ����
	int score;

	//��ŷ ����� ���� username�� score �ֵ� (���߿� �̰� ���Ϸ� �����ؾ���.)
	vector<pair<int, string>> ranking;

public:
	//GameOverScene���� GameController�κ��� ���� ���� ������ Score�� �޾ƿ��� ����.
	int getScore();

	//Game���� ���� ���� ������ Score�� GameController�� �޾ƿ��� ����.
	void setScore(int);

	//GameOverScene���� �Է¹��� user�� score�� pair�� ranking�� �����ϱ� ����. (score ���� 10���� ����.)
	void addUser(string);

	//���� ����:�ڱ� �� �ǵ�ȴ���, �̵������ �ݴ�� ����������, ���� ��Ҵ��� (���� ����)
	void endGameCondition();
};