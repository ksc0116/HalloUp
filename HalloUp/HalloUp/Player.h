#pragma once
#include "Jokbo.h"
#include "Card.h"

class Player
{
public:
	int id;
	int index = -1;
	int candy;

	JOKBO myJokbo;	// ���� �������� �ʱ�ȭ �ʿ���
	bool isDie;		// ���� �ý��� ���� �� ���� �ʱ�ȭ �ʿ���
	bool isNoCandy;
	bool isGameOver;
	bool isCall;	// ���� �ý��� ���� �� ���� �ʱ�ȭ �ʿ���
	bool isPreference;	
	Card myCard[3];	// ���� �������� �ʱ�ȭ �ʿ���
	Card mySelectCard[2];	// ���� �������� �ʱ�ȭ �ʿ���
	Card myOpenCard;	// ���� �������� �ʱ�ȭ �ʿ���
	int cardIndex;
	int myBettingCandy;	// ���� �ý��� ���� �� ���� �ʱ�ȭ �ʿ���

	Player();	// PlayerGetCard���� �ڵ����� �ʱ�ȭ

	// �׽�Ʈ�� ����
	bool isLogIn = false;

	bool isBet = false;

	bool isCircuit = false;

	bool isSelectMatchCard;	// ���� ������ �ʱ�ȭ �ʿ���

	void PlayerGetCard(Card card);
};