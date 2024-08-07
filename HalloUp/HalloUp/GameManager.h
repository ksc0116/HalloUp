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

// 키보드 값
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SELECT 4
// 콘솔창 사이즈 변경
#define COMMAND_SIZE 256

// 게임 중 선택 값
#define ONE 100
#define TWO 200
#define THREE 300
#define FOUR 400 
#define FIVE 500
#define SIX 600
#define SEVEN 700
#define EIGHT 800
#define NINE 900

// 기본 판 돈
#define BASIC_GAME_MONEY 100

class TcpClient;
class Player;
class Card;

// 게임에 필요한 변수들
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
extern bool isGameOver;	// 게임이 끝났는지 확인 하는 변수
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

	// 초기화면 메뉴 선택 함수
	int SelectMenu();		// GamaManager

	// 카드에게 넘버 부여하는 함수
	void SetCardNumber();	// GameManager

	// 카드를 나눠주는 함수
	void HandOutCard();		// GameManager

	// 메인 게임 로직 함수
	void MainGameLogic();	// GameManager

	// 게임시작 버튼 함수
	void GameStart();	// GameManager

	// 카드 섞는 함수
	void MixCard(int* p_card);	// GameManager

	// 모든 입력 버퍼 비우는 함수
	void ClearInputBuffer();	// GameManager

	// 기본 판 돈 내는 함수
	void ParticipateCandy(); // GameManager

	// 한 플레이어가 베팅을 했을 때 총 게임캔디와 앞사람의 베팅 캔디를 최신화
	void UpdateTotalGameCandyAndFrontBetcandy(int playerIndex, int betInfo);	// GameManager

	// 한 플레이어가 베팅을 했을 때 다른 플레이어들에게 그 정보를 최신화 해주어야함
	void UpdatePlayerBettingInfo(int playerIndex, int betInfo);	// GameManager

	// 카드 조합 선택하는 함수
	void MatchCardSelect();	// GameManager

	// 다른 플레이어에게 내가 선택한 카드조합 정보 넘기기
	void UpdateMatchCardSelect(int cardIndex1, int cardIndex2, int playerIndex);	// GameManager

	// 승자 정하는 함수
	void DecideWinnerPlayer(int winnerPlayerIndex);

	// 게임 리셋하는 함수
	bool ResetGame();	// GameManager

	void GetOpenCardInfo(int playerIndex, int cardIndex); // GameManager

	// 베팅이 가능한 지 확인 하는 함수 (true면 베팅 가능 false면 불가능)
	bool IsBettingAble(int needCandy); // 현재 나의 플레이어 기준	// GameManager

	void AllPlayerLogIn();	// GameManager

	void ShowAllPlayerMatchCard();	// GameManager

	void CurrentLogInPlayerCandyPrint(); // GameManager

	void SendPreferencePlayerEndGame();	// GamaManager
};
//===========================CLASS=======================================



//// 게임 제목 출력 함수
//void PrintGameTitle();		// PrintManager

//// 초기화면 메뉴 선택 함수
//int SelectMenu();		// GamaManager

// 게임 정보 출력 함수
//void GameInfoDraw();		// PrintManager

//// 메인 게임 창 그려주는 함수
//void DrawMainGameScreen(Player* p_player);  // PrintManager

//// 카드 조합 보여주는 함수
//void DrawCardCombination(Player p_player);		// PrintManager

//// 콘솔창 위치 바꾸는 함수
//void ChangeConsloePosition(int x, int y);		// ConsoleManager

//// 콘솔에서 커서 위치 바꾸는 함수
//void GoToXY(int x, int y);		// ConsoleManager

//// 글자 색 바꾸는 함수
//void SetColor(short color);		// Consolemanager

// 키보드 입력 처리 함수 (1, 2, 3, 6, 7, 8, 9)
//int KeyBoardControlNumber(Player* player);

//// 키도브 입력 처리 함수 (상, 하, 좌, 우, 선택)
//int KeyBoardControl();		//InputManager

//// 콘솔에서 커서 안보이게 하는 함수
//void CursorView();		// ConsoleManager

//// 콘솔창 크기 바꾸는 함수
//void ChangeConsoleSize(int x, int y);		// ConsoleManager

//// 글씨 크기 바꾸는 함수
//void ChangeFont();		// ConsoleManger

//// 카드에게 넘버 부여하는 함수
//void SetCardNumber();	// GameManager

//// 카드를 나눠주는 함수
//void HandOutCard();		// GameManager

//// 카드를 돌릴 때 알맞게 이미지 그리는 함수
//void DrawPlayerCard(int curPlayerNumber, int cardNumber);	// PrintManager

//// 어떤 카드를 그려야 할 지 알려주는 함수
//char(*GetDrawImage(int cardNumber))[20];	// PrintManager

//// 메인 게임 로직 함수
//void MainGameLogic();	// GameManager

//// 게임시작 버튼 함수
//void GameStart();	// GameManager

//// 카드 섞는 함수
//void MixCard(time_t seed);	// GameManager

// 카드 오픈 함수들=================================================================
//// 나의 카드 중 뭘 오픈할 지 입력하는 함수 (서버에 정보까지 보냄)
//void OpenCardInput();	// InputManager

//// 모든 플레이어가 카드를 선택하면 화면에 출력하는 함수
//void PrintAllPlayerOpenCard();	// Printmanager
//=================================================================================

//// 모든 입력 버퍼 비우는 함수
//void ClearInputBuffer();	// GameManager

//// 1 2만 입력 가능한 키보드 입력 함수
//int KeyBoardControlOneTwo();	// InputManager

//// 1 2 3만 입력 가능한 키보드 입력 함수
//int KeyBoardControlOneTwoThree();	// Inputmanager

//// 4 5 6 7 8 9만 입력 가능한 함수
//int KeyBoardControlBettingSystem();	//  InputManager

//// 기본 판 돈 내는 함수
//void ParticipateCandy(); // GameManager

//// 맨 처음 모두가 들어왔을 때 플레이어 캔디 다시 출력
//void FirstAllPlayerCandyRePrint();	// PrintManager

// 베팅 시스템 함수
//void BettingSystem();

// 베팅 관련 함수==============================================================
//// 베팅 입력
//bool BettingInput(bool isFirst);	// InputManager

//// 한 플레이어가 베팅을 했을 때 총 게임캔디와 앞사람의 베팅 캔디를 최신화
//void UpdateTotalGameCandyAndFrontBetcandy(int playerIndex,int betInfo);	// GameManager
 
//// 한 플레이어가 베팅을 했을 때 다른 플레이어들에게 그 정보를 최신화 해주어야함
//void UpdatePlayerBettingInfo(int playerIndex, int betInfo);	// GameManager

//// 각 플레이어가 입력한 베팅 정보 가져오기
//void PrintBettingInfo(int playerIndex, int betInfoIndex);	// PrintManager

//// 베팅을 했을 때 모든 플레이어의 캔디 최신화하는 함수
//void PrintPlayerCandy(int playerIndex);	// PrintManager

//// 베팅을 했을 때 바뀌는 게임 총 캔디를 출력해줌
//void PrintTotalGameCandy();		// PrintManager

//// 베팅이 완전 끝나면 베팅 정보 지우는 함수
//void DeleteBettingInfo();	// PrintManager

//// 자동으로 현재 베팅하는 사람 가리키는 화살표 출력
//void PrintArrow(int playerNumber);	// PrintManager

//// 화살표 지우는 함수
//void DleteArrow();	// PrintManager

//============================================================================

//// 카드 조합 선택하는 함수
//void MatchCardSelect();	// GameManager

//// 다른 플레이어에게 내가 선택한 카드조합 정보 넘기기
//void UpdateMatchCardSelect(int cardIndex1,int cardIndex2,int playerIndex);	// GameManager

//// 모두가 승부 카드 선택하면 동시에 화면에 뿌려줌
//void PrintAllPlayerMatchCard();		// PrintManager
//==============================================================================

// 승자 가리는 함수==============================================================
//// 승자 정하는 함수
//void DecideWinnerPlayer(int winnerPlayerIndex);	// 이 함수가 끝났을 때 gameOverPlayerCOunt값 결정 // GameManager

//// 게임 리셋하는 함수
//bool ResetGame();	// GameManager

//void PrintPlayerState(Player* p_player);	// PrintManager


//=============================================================================


//// 베팅이 가능한 지 확인 하는 함수 (true면 베팅 가능 false면 불가능)
//bool IsBettingAble(int needCandy); // 현재 나의 플레이어 기준	// GameManager

//// 베팅 후 나의 캔디 현황 보여주는 함수
//void PrintCurrentMyCandy(int playerIndex);	// PrintManager

//// 나의 플레이어가 어떤 것을 베팅 했는지 보여주는 함수
//void ShowBettingInfo(int playerIndex,int bettingInfo);	// PrintManager

//// 각 플레이어가 선택한 카드 화면에 뿌려주는 함수
//void ShowAllplayerOpenCard(int playerIndex);	// PrintManager

//// 카드 조합 보여주기
//void ShowCardCombination(Player player);	// PrintManager

//// 모든 이미지 지우는 함수
//void DeleteAllImage();	// PrintManager


// TCP Client에서 사용 할 함수들
//--------------------------------------
//void GetOpenCardInfo(int playerIndex, int cardIndex); // GameManager

//void AllPlayerLogIn();	// GameManager

//void ShowAllPlayerMatchCard();	// GameManager

//void CurrentLogInPlayerCandyPrint(); // GameManager

//void SendPreferencePlayerEndGame();	// GamaManager