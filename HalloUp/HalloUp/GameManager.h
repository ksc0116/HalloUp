#pragma once
#include <iostream>
//#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

#include "ConsoleManager.h"
#include "InputManager.h"
#include "PrintManager.h"

#include "Graphics.h"
#include "Player.h"

#include "TcpClient.h"
#include "Jokbo.h"
#include "sound.h"
//#include "Player.h"
//#include "TcpClient.h"
//#include "PacketC2S.h"

// Ű���� ��
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SELECT 4
// �ܼ�â ������ ����
#define COMMAND_SIZE 256

// ���� �� ���� ��
#define ONE 100
#define TWO 200
#define THREE 300
#define FOUR 400 
#define FIVE 500
#define SIX 600
#define SEVEN 700
#define EIGHT 800
#define NINE 900

// �⺻ �� ��
#define BASIC_GAME_MONEY 100

class TcpClient;
class Player;
class Card;

// ���ӿ� �ʿ��� ������
extern TcpClient TCP_Client;
extern Player player;
extern Player players[4];
extern Card card[20];
extern int cardIndex;
extern int handOutIndex;
extern int totalGameCandy;
extern int maxBettingCandy;
extern int frontPlayerBettingCandy;
extern int preferencePlayerIndex;
extern int tempPreferencePlayerIndex;
extern int diePlayerCount;
extern int callPlayerCount;
extern int gameOverPlayerCount;
extern bool isGameOver;	// ������ �������� Ȯ�� �ϴ� ����
extern bool isAllPlayerLogIn;
extern int curPlayerCount;
extern int tempMaxBettingCandy;
extern int getPacketCount;
extern bool anotherBetWait;
extern int betCount;
extern bool isPlayerBet;
extern bool isPreferencePlayerDie;
extern int winnerPlayerIndex;
//

class GameManager
{
private:
	GameManager() {}
	GameManager(const GameManager& ref) {}
	~GameManager() {}
public:
	static GameManager& Instance();

	// �ʱ�ȭ�� �޴� ���� �Լ�
	int SelectMenu();		// GamaManager

	// ī�忡�� �ѹ� �ο��ϴ� �Լ�
	void SetCardNumber();	// GameManager

	// ī�带 �����ִ� �Լ�
	void HandOutCard();		// GameManager

	// ���� ���� ���� �Լ�
	void MainGameLogic();	// GameManager

	// ���ӽ��� ��ư �Լ�
	void GameStart();	// GameManager

	// ī�� ���� �Լ�
	void MixCard(int* p_card);	// GameManager

	// ��� �Է� ���� ���� �Լ�
	void ClearInputBuffer();	// GameManager

	// �⺻ �� �� ���� �Լ�
	void ParticipateCandy(); // GameManager

	// �� �÷��̾ ������ ���� �� �� ����ĵ��� �ջ���� ���� ĵ�� �ֽ�ȭ
	void UpdateTotalGameCandyAndFrontBetcandy(int playerIndex, int betInfo);	// GameManager

	// �� �÷��̾ ������ ���� �� �ٸ� �÷��̾�鿡�� �� ������ �ֽ�ȭ ���־����
	void UpdatePlayerBettingInfo(int playerIndex, int betInfo);	// GameManager

	// ī�� ���� �����ϴ� �Լ�
	void MatchCardSelect();	// GameManager

	// �ٸ� �÷��̾�� ���� ������ ī������ ���� �ѱ��
	void UpdateMatchCardSelect(int cardIndex1, int cardIndex2, int playerIndex);	// GameManager

	// ���� ���ϴ� �Լ�
	void DecideWinnerPlayer(int winnerPlayerIndex);

	// ���� �����ϴ� �Լ�
	bool ResetGame();	// GameManager

	void GetOpenCardInfo(int playerIndex, int cardIndex); // GameManager

	// ������ ������ �� Ȯ�� �ϴ� �Լ� (true�� ���� ���� false�� �Ұ���)
	bool IsBettingAble(int needCandy); // ���� ���� �÷��̾� ����	// GameManager

	void AllPlayerLogIn();	// GameManager

	void ShowAllPlayerMatchCard();	// GameManager

	void CurrentLogInPlayerCandyPrint(); // GameManager

	void SendPreferencePlayerEndGame();	// GamaManager
};
//===========================CLASS=======================================



//// ���� ���� ��� �Լ�
//void PrintGameTitle();		// PrintManager

//// �ʱ�ȭ�� �޴� ���� �Լ�
//int SelectMenu();		// GamaManager

// ���� ���� ��� �Լ�
//void GameInfoDraw();		// PrintManager

//// ���� ���� â �׷��ִ� �Լ�
//void DrawMainGameScreen(Player* p_player);  // PrintManager

//// ī�� ���� �����ִ� �Լ�
//void DrawCardCombination(Player p_player);		// PrintManager

//// �ܼ�â ��ġ �ٲٴ� �Լ�
//void ChangeConsloePosition(int x, int y);		// ConsoleManager

//// �ֿܼ��� Ŀ�� ��ġ �ٲٴ� �Լ�
//void GoToXY(int x, int y);		// ConsoleManager

//// ���� �� �ٲٴ� �Լ�
//void SetColor(short color);		// Consolemanager

// Ű���� �Է� ó�� �Լ� (1, 2, 3, 6, 7, 8, 9)
//int KeyBoardControlNumber(Player* player);

//// Ű���� �Է� ó�� �Լ� (��, ��, ��, ��, ����)
//int KeyBoardControl();		//InputManager

//// �ֿܼ��� Ŀ�� �Ⱥ��̰� �ϴ� �Լ�
//void CursorView();		// ConsoleManager

//// �ܼ�â ũ�� �ٲٴ� �Լ�
//void ChangeConsoleSize(int x, int y);		// ConsoleManager

//// �۾� ũ�� �ٲٴ� �Լ�
//void ChangeFont();		// ConsoleManger

//// ī�忡�� �ѹ� �ο��ϴ� �Լ�
//void SetCardNumber();	// GameManager

//// ī�带 �����ִ� �Լ�
//void HandOutCard();		// GameManager

//// ī�带 ���� �� �˸°� �̹��� �׸��� �Լ�
//void DrawPlayerCard(int curPlayerNumber, int cardNumber);	// PrintManager

//// � ī�带 �׷��� �� �� �˷��ִ� �Լ�
//char(*GetDrawImage(int cardNumber))[20];	// PrintManager

//// ���� ���� ���� �Լ�
//void MainGameLogic();	// GameManager

//// ���ӽ��� ��ư �Լ�
//void GameStart();	// GameManager

//// ī�� ���� �Լ�
//void MixCard(time_t seed);	// GameManager

// ī�� ���� �Լ���=================================================================
//// ���� ī�� �� �� ������ �� �Է��ϴ� �Լ� (������ �������� ����)
//void OpenCardInput();	// InputManager

//// ��� �÷��̾ ī�带 �����ϸ� ȭ�鿡 ����ϴ� �Լ�
//void PrintAllPlayerOpenCard();	// Printmanager
//=================================================================================

//// ��� �Է� ���� ���� �Լ�
//void ClearInputBuffer();	// GameManager

//// 1 2�� �Է� ������ Ű���� �Է� �Լ�
//int KeyBoardControlOneTwo();	// InputManager

//// 1 2 3�� �Է� ������ Ű���� �Է� �Լ�
//int KeyBoardControlOneTwoThree();	// Inputmanager

//// 4 5 6 7 8 9�� �Է� ������ �Լ�
//int KeyBoardControlBettingSystem();	//  InputManager

//// �⺻ �� �� ���� �Լ�
//void ParticipateCandy(); // GameManager

//// �� ó�� ��ΰ� ������ �� �÷��̾� ĵ�� �ٽ� ���
//void FirstAllPlayerCandyRePrint();	// PrintManager

// ���� �ý��� �Լ�
//void BettingSystem();

// ���� ���� �Լ�==============================================================
//// ���� �Է�
//bool BettingInput(bool isFirst);	// InputManager

//// �� �÷��̾ ������ ���� �� �� ����ĵ��� �ջ���� ���� ĵ�� �ֽ�ȭ
//void UpdateTotalGameCandyAndFrontBetcandy(int playerIndex,int betInfo);	// GameManager
 
//// �� �÷��̾ ������ ���� �� �ٸ� �÷��̾�鿡�� �� ������ �ֽ�ȭ ���־����
//void UpdatePlayerBettingInfo(int playerIndex, int betInfo);	// GameManager

//// �� �÷��̾ �Է��� ���� ���� ��������
//void PrintBettingInfo(int playerIndex, int betInfoIndex);	// PrintManager

//// ������ ���� �� ��� �÷��̾��� ĵ�� �ֽ�ȭ�ϴ� �Լ�
//void PrintPlayerCandy(int playerIndex);	// PrintManager

//// ������ ���� �� �ٲ�� ���� �� ĵ�� �������
//void PrintTotalGameCandy();		// PrintManager

//// ������ ���� ������ ���� ���� ����� �Լ�
//void DeleteBettingInfo();	// PrintManager

//// �ڵ����� ���� �����ϴ� ��� ����Ű�� ȭ��ǥ ���
//void PrintArrow(int playerNumber);	// PrintManager

//// ȭ��ǥ ����� �Լ�
//void DleteArrow();	// PrintManager

//============================================================================

//// ī�� ���� �����ϴ� �Լ�
//void MatchCardSelect();	// GameManager

//// �ٸ� �÷��̾�� ���� ������ ī������ ���� �ѱ��
//void UpdateMatchCardSelect(int cardIndex1,int cardIndex2,int playerIndex);	// GameManager

//// ��ΰ� �º� ī�� �����ϸ� ���ÿ� ȭ�鿡 �ѷ���
//void PrintAllPlayerMatchCard();		// PrintManager
//==============================================================================

// ���� ������ �Լ�==============================================================
//// ���� ���ϴ� �Լ�
//void DecideWinnerPlayer(int winnerPlayerIndex);	// �� �Լ��� ������ �� gameOverPlayerCOunt�� ���� // GameManager

//// ���� �����ϴ� �Լ�
//bool ResetGame();	// GameManager

//void PrintPlayerState(Player* p_player);	// PrintManager


//=============================================================================


//// ������ ������ �� Ȯ�� �ϴ� �Լ� (true�� ���� ���� false�� �Ұ���)
//bool IsBettingAble(int needCandy); // ���� ���� �÷��̾� ����	// GameManager

//// ���� �� ���� ĵ�� ��Ȳ �����ִ� �Լ�
//void PrintCurrentMyCandy(int playerIndex);	// PrintManager

//// ���� �÷��̾ � ���� ���� �ߴ��� �����ִ� �Լ�
//void ShowBettingInfo(int playerIndex,int bettingInfo);	// PrintManager

//// �� �÷��̾ ������ ī�� ȭ�鿡 �ѷ��ִ� �Լ�
//void ShowAllplayerOpenCard(int playerIndex);	// PrintManager

//// ī�� ���� �����ֱ�
//void ShowCardCombination(Player player);	// PrintManager

//// ��� �̹��� ����� �Լ�
//void DeleteAllImage();	// PrintManager


// TCP Client���� ��� �� �Լ���
//--------------------------------------
//void GetOpenCardInfo(int playerIndex, int cardIndex); // GameManager

//void AllPlayerLogIn();	// GameManager

//void ShowAllPlayerMatchCard();	// GameManager

//void CurrentLogInPlayerCandyPrint(); // GameManager

//void SendPreferencePlayerEndGame();	// GamaManager