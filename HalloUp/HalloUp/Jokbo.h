#pragma once
class Player;

enum JOKBO
{
	DRAW,	// ���� ���º�	
	GT38,	// 38����
	AHOS,	// ������(4����, 7���� : 38���� �̸� ���)
	GT18,	// 18����
	GT13,	// 13����
	ZTT,	// �嶯(10��)
	TTJ,	// ������(3��, 7���� : �嶯 �̸� ���)
	TT9,	// 9��
	TT8,	// 8��
	TT7,	// 7��
	TT6,	// 6��
	TT5,	// 5��	
	TT4,	// 4��	
	TT3,	// 3��	
	TT2,	// 2��	
	TT1,	// 1��	
	ALI,	// �˸�(1��, 2��)	
	DS,		// ����(1��, 4��)	
	GBB,	// ����(1��, 9��)	
	ZBB,	// ���(1��, 10��)	
	ZS,		// ���(4��, 10��)	
	SYG,	// ����/���(4��, 6��)	
	KKT9,	// 9��	
	KKT8,	// 8��	
	KKT7,	// 7��	
	KKT6,	// 6��	
	KKT5,	// 5��	
	KKT4,	// 4��	
	KKT3,	// 3��	
	KKT2,	// 2��	
	KKT1,	// 1��	
	KKT0,	// 0��	
	YET,	// ���� ���� ��	
};

void JokboGubun(Player* player, int cardIndex1, int cardIndex2);
int WinnerPlayerGubun(Player* player);
int CompareJokbo(Player* player);
void JokboGubun(Player* player, JOKBO* jockbo);