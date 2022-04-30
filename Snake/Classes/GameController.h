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
	vector<pair<string, int>> ranking;

public:
	//GameOverScene���� GameController�κ��� ���� ���� ������ Score�� �޾ƿ��� ����.
	int getScore();

	//Game���� ���� ���� ������ Score�� GameController�� �޾ƿ��� ����.
	void setScore();

	//GameOverScene���� �Է¹��� user�� score�� pair�� ranking�� �����ϱ� ����.
	void adduser(string);

	//ranking�� �ִ� user�� score pair�� username�� ���ڷ� �޾� ����� ����.
	void deleteUser(string);

	//���� ����:�ڱ� �� �ǵ�ȴ���, �̵������ �ݴ�� ����������, ���� ��Ҵ��� (���� ����)
	void endGameCondition();
};