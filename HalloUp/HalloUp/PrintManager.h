#pragma once
#include <string>
using namespace std;
class Player;

extern char _winMessage[20][40];
extern char _dieMessage[20][40];
extern char _bbingMessage[9][30];
extern char _ddaDangMessage[9][30];
extern char _callMessage[9][30];
extern char _quarterMessage[9][30];
extern char _halfMessage[9][30];

enum class CardArea
{
	MAIN1, MAIN2, MAIN3, P1_1, P1_2, P2_1, P2_2, P3_1, P3_2, P4_1, P4_2
};

enum class InfoArea
{
	INFO1, INFO2, INFO3
};

enum class BetInfo
{
	DDIE, DDADANG, BBING, QUARTER, HALF, CALL
};

enum Color
{
	BLACK, DARKBLUE, GREEN, CYAN, DARKRED, PURPLE, DARKYELLOW, FADEWHITE, GRAY, BLUE, LIGHTGREEN, LIGHTBLUE, RED, PINK, YELLOW, WHITE
};

class PrintManager
{
private:
	PrintManager() {}
	PrintManager(const PrintManager& ref) {}
	~PrintManager() {}
public:
	static PrintManager& Instance();

	// ���� ���� ��� �Լ�
	void PrintGameTitle();		// PrintManager

	// ���� ���� ��� �Լ�
	void GameInfoDraw();		// PrintManager

	// ���� ���� â �׷��ִ� �Լ�
	void DrawMainGameScreen(Player* p_player);  // PrintManager

	// ī�� ���� �����ִ� �Լ�
	void DrawCardCombination(Player p_player);		// PrintManager

	// ī�带 ���� �� �˸°� �̹��� �׸��� �Լ�
	void DrawPlayerCard(int curPlayerNumber, int cardNumber);	// PrintManager

	// � ī�带 �׷��� �� �� �˷��ִ� �Լ�
	char(*GetDrawImage(int cardNumber))[20];	// PrintManager

	// ��� �÷��̾ ī�带 �����ϸ� ȭ�鿡 ����ϴ� �Լ�
	void PrintAllPlayerOpenCard();	// Printmanager

	// �� ó�� ��ΰ� ������ �� �÷��̾� ĵ�� �ٽ� ���
	void FirstAllPlayerCandyRePrint();	// PrintManager

	// �� �÷��̾ �Է��� ���� ���� ��������
	void PrintBettingInfo(int playerIndex, int betInfoIndex);	// PrintManager

	// ������ ���� �� ��� �÷��̾��� ĵ�� �ֽ�ȭ�ϴ� �Լ�
	void PrintPlayerCandy(int playerIndex);	// PrintManager

	// ������ ���� �� �ٲ�� ���� �� ĵ�� �������
	void PrintTotalGameCandy();		// PrintManager

	// ������ ���� ������ ���� ���� ����� �Լ�
	void DeleteBettingInfo();	// PrintManager

	// �ڵ����� ���� �����ϴ� ��� ����Ű�� ȭ��ǥ ���
	void PrintArrow(int playerNumber);	// PrintManager

	// ȭ��ǥ ����� �Լ�
	void DleteArrow();	// PrintManager

	// ��ΰ� �º� ī�� �����ϸ� ���ÿ� ȭ�鿡 �ѷ���
	void PrintAllPlayerMatchCard();		// PrintManager

	void PrintPlayerState(Player* p_player);	// PrintManager

	// ���� �� ���� ĵ�� ��Ȳ �����ִ� �Լ�
	void PrintCurrentMyCandy(int playerIndex);	// PrintManager

	// ���� �÷��̾ � ���� ���� �ߴ��� �����ִ� �Լ�
	void ShowBettingInfo(int playerIndex, int bettingInfo);	// PrintManager

	// �� �÷��̾ ������ ī�� ȭ�鿡 �ѷ��ִ� �Լ�
	void ShowAllplayerOpenCard(int playerIndex);	// PrintManager

	// ī�� ���� �����ֱ�
	void ShowCardCombination(Player player);	// PrintManager

	// ��� �̹��� ����� �Լ�
	void DeleteAllImage();	// PrintManager

	void ResetTextColor();

	void AddDecoration();

	void PrintImage(CardArea _area, char _arr[][20]);

	void PrintInfo(InfoArea _area, string _str);

	void FillArea(bool _isShort, int _startX, int _startY, int _endX, int _endY);

	void EraseArea(bool _isShort, int _startX, int _startY, int _endX, int _endY);

	void EraseArea(InfoArea _area);

	void EraseArea(CardArea _area);

	void PrintWin(int playerNo);

	void DrawRow(int _x, int _y, int length);

	void DrawColumn(int _x, int _y, int length);

	void DrawPlayerArrow(int playerNo);

	void ErasePlayerArrow(int playerNo);

	void DrawPlayerCardsOnBoard(int playerNo);

	void PutCardFrames();

	void DrawGameButtons();

	void PrintDie(int playerNo);

	void DrawMainBoard(Player* p_player);

	void PrintAllBettingButton();

	void DeleteSpecificBettingButton(bool isBbing, bool isDD, bool isCall,bool isQuarter, bool isHalf);

	void DeleteAllBettingButton();
};

