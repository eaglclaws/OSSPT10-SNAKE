#pragma once
#include <string>

using namespace std;

class GameController {

	//score ���
	int score;

	//������ġ�� food ��ġ
	void food();

	//food�� �Ծ����� üũ (���⼭ �� �ص� ��.)
	void checkFood();

	//�÷��̾� �̸�
	string playerName;

	//��ŷ ���(int* �ӽ�, �ܺ� ���Ϸ� �ؾ� �ȳ��ư�)
	int* ranking;

	//���� ����
	void endGame();

	//���� ����:�ڱ� �� �ǵ�ȴ���, ���� ��Ҵ���, �̵������ �ݴ�� ����������, 

};