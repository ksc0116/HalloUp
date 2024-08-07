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

	// 게임 제목 출력 함수
	void PrintGameTitle();		// PrintManager

	// 게임 정보 출력 함수
	void GameInfoDraw();		// PrintManager

	// 메인 게임 창 그려주는 함수
	void DrawMainGameScreen(Player* p_player);  // PrintManager

	// 카드 조합 보여주는 함수
	void DrawCardCombination(Player p_player);		// PrintManager

	// 카드를 돌릴 때 알맞게 이미지 그리는 함수
	void DrawPlayerCard(int curPlayerNumber, int cardNumber);	// PrintManager

	// 어떤 카드를 그려야 할 지 알려주는 함수
	char(*GetDrawImage(int cardNumber))[20];	// PrintManager

	// 모든 플레이어가 카드를 선택하면 화면에 출력하는 함수
	void PrintAllPlayerOpenCard();	// Printmanager

	// 맨 처음 모두가 들어왔을 때 플레이어 캔디 다시 출력
	void FirstAllPlayerCandyRePrint();	// PrintManager

	// 각 플레이어가 입력한 베팅 정보 가져오기
	void PrintBettingInfo(int playerIndex, int betInfoIndex);	// PrintManager

	// 베팅을 했을 때 모든 플레이어의 캔디 최신화하는 함수
	void PrintPlayerCandy(int playerIndex);	// PrintManager

	// 베팅을 했을 때 바뀌는 게임 총 캔디를 출력해줌
	void PrintTotalGameCandy();		// PrintManager

	// 베팅이 완전 끝나면 베팅 정보 지우는 함수
	void DeleteBettingInfo();	// PrintManager

	// 자동으로 현재 베팅하는 사람 가리키는 화살표 출력
	void PrintArrow(int playerNumber);	// PrintManager

	// 화살표 지우는 함수
	void DleteArrow();	// PrintManager

	// 모두가 승부 카드 선택하면 동시에 화면에 뿌려줌
	void PrintAllPlayerMatchCard();		// PrintManager

	void PrintPlayerState(Player* p_player);	// PrintManager

	// 베팅 후 나의 캔디 현황 보여주는 함수
	void PrintCurrentMyCandy(int playerIndex);	// PrintManager

	// 나의 플레이어가 어떤 것을 베팅 했는지 보여주는 함수
	void ShowBettingInfo(int playerIndex, int bettingInfo);	// PrintManager

	// 각 플레이어가 선택한 카드 화면에 뿌려주는 함수
	void ShowAllplayerOpenCard(int playerIndex);	// PrintManager

	// 카드 조합 보여주기
	void ShowCardCombination(Player player);	// PrintManager

	// 모든 이미지 지우는 함수
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

