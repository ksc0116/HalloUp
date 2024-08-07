#pragma once
class Player;

enum JOKBO
{
	DRAW,	// Á·º¸ ¹«½ÂºÎ	
	GT38,	// 38±¤¶¯
	AHOS,	// ¾ÏÇà¾î»ç(4¿­²ý, 7¿­²ý : 38±¤¶¯ ¹Ì¸¸ ¿ì½Â)
	GT18,	// 18±¤¶¯
	GT13,	// 13±¤¶¯
	ZTT,	// Àå¶¯(10¶¯)
	TTJ,	// ¶¯ÀâÀÌ(3±¤, 7¿­²ý : Àå¶¯ ¹Ì¸¸ ¿ì½Â)
	TT9,	// 9¶¯
	TT8,	// 8¶¯
	TT7,	// 7¶¯
	TT6,	// 6¶¯
	TT5,	// 5¶¯	
	TT4,	// 4¶¯	
	TT3,	// 3¶¯	
	TT2,	// 2¶¯	
	TT1,	// 1¶¯	
	ALI,	// ¾Ë¸®(1¿ù, 2¿ù)	
	DS,		// µ¶»ç(1¿ù, 4¿ù)	
	GBB,	// ±¸»æ(1¿ù, 9¿ù)	
	ZBB,	// Àå»æ(1¿ù, 10¿ù)	
	ZS,		// Àå»ç(4¿ù, 10¿ù)	
	SYG,	// ¼¼·ú/»ç·ú(4¿ù, 6¿ù)	
	KKT9,	// 9²ý	
	KKT8,	// 8²ý	
	KKT7,	// 7²ý	
	KKT6,	// 6²ý	
	KKT5,	// 5²ý	
	KKT4,	// 4²ý	
	KKT3,	// 3²ý	
	KKT2,	// 2²ý	
	KKT1,	// 1²ý	
	KKT0,	// 0²ý	
	YET,	// Á·º¸ ±¸ºÐ Àü	
};

void JokboGubun(Player* player, int cardIndex1, int cardIndex2);
int WinnerPlayerGubun(Player* player);
int CompareJokbo(Player* player);
void JokboGubun(Player* player, JOKBO* jockbo);