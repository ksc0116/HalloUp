#pragma once

extern char _ghost1[20][20];
//������ 2
extern char _pumpkin1[20][20];
//���ڻ� 3
extern char _spider1[20][20];
//���ڻ� 4
extern char _coffin1[20][20];
//���ڻ� 5
extern char _fox1[20][20];
//���ڻ� 6
extern char _hat1[20][20];
//���ڻ� 7
extern char _cat1[20][20];
//���ڻ� 8
extern char _bat1[20][20];
//���ڻ� 9
extern char _skull1[20][20];
//���ڻ� 10
extern char _bone1[20][20];
//���ڻ� 11
extern char _ghost2[20][20];
//���ڻ� 12
extern char _pumpkin2[20][20];
//���ڻ� 13
extern char _spider2[20][20];
//���ڻ� 14
extern char _coffin2[20][20];
//���ڻ� 15
extern char _fox2[20][20];
//���ڻ� 16
extern char _hat2[20][20];
//���ڻ� 17
extern char _cat2[20][20];
//���ڻ� 18
extern char _bat2[20][20];
//���ڻ� 19
extern char _skull2[20][20];
//���ڻ� 20
extern char _bone2[20][20];
// ī�� �޸�
extern char back[20][20];




class Card
{
public:
	int cardNumber;
	int cardIndex;
	// ī�� �ѹ� Get �Լ�
	int GetcardNumber();
	// ī�� �ѹ� ���� �Լ�
	void SetCardNumber(int number);
};
