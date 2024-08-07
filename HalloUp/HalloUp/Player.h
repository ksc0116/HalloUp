#pragma once
#include "Jokbo.h"
#include "Card.h"

class Player
{
public:
	int id;
	int index = -1;
	int candy;

	JOKBO myJokbo;	// 승자 가려지면 초기화 필요함
	bool isDie;		// 베팅 시스템 끝날 때 마다 초기화 필요함
	bool isNoCandy;
	bool isGameOver;
	bool isCall;	// 베팅 시스템 끝날 때 마다 초기화 필요함
	bool isPreference;	
	Card myCard[3];	// 승자 가려지면 초기화 필요함
	Card mySelectCard[2];	// 승자 가려지면 초기화 필요함
	Card myOpenCard;	// 승자 가려지면 초기화 필요함
	int cardIndex;
	int myBettingCandy;	// 베팅 시스템 끝날 때 마다 초기화 필요함

	Player();	// PlayerGetCard에서 자동으로 초기화

	// 테스트용 변수
	bool isLogIn = false;

	bool isBet = false;

	bool isCircuit = false;

	bool isSelectMatchCard;	// 게임 끝나면 초기화 필요함

	void PlayerGetCard(Card card);
};