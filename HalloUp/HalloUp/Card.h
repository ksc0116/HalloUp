#pragma once

extern char _ghost1[20][20];
//순서상 2
extern char _pumpkin1[20][20];
//숫자상 3
extern char _spider1[20][20];
//숫자상 4
extern char _coffin1[20][20];
//숫자상 5
extern char _fox1[20][20];
//숫자상 6
extern char _hat1[20][20];
//숫자상 7
extern char _cat1[20][20];
//숫자상 8
extern char _bat1[20][20];
//숫자상 9
extern char _skull1[20][20];
//숫자상 10
extern char _bone1[20][20];
//숫자상 11
extern char _ghost2[20][20];
//숫자상 12
extern char _pumpkin2[20][20];
//숫자상 13
extern char _spider2[20][20];
//숫자상 14
extern char _coffin2[20][20];
//숫자상 15
extern char _fox2[20][20];
//숫자상 16
extern char _hat2[20][20];
//숫자상 17
extern char _cat2[20][20];
//숫자상 18
extern char _bat2[20][20];
//숫자상 19
extern char _skull2[20][20];
//숫자상 20
extern char _bone2[20][20];
// 카드 뒷면
extern char back[20][20];




class Card
{
public:
	int cardNumber;
	int cardIndex;
	// 카드 넘버 Get 함수
	int GetcardNumber();
	// 카드 넘버 셋팅 함수
	void SetCardNumber(int number);
};
