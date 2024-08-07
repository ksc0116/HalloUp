#include "GameManager.h"
#include "sound.h"

using namespace std;

TcpClient TCP_Client;
Player player;
Player players[4];
Card card[20];
int cardIndex = 0;		// 승자 가려지면 초기화 필요함
int handOutIndex = 1;	// 승자 가려지면 초기화 필요함
int totalGameCandy = 0;	// 승자 가려지면 초기화 필요함
int maxBettingCandy;	// 베팅 시스템이 끝날 때 마다 초기화 필요함
int frontPlayerBettingCandy;
int preferencePlayerIndex;
int tempPreferencePlayerIndex;
int diePlayerCount;		// 승자 가려지면 초기화 필요함
int callPlayerCount;
int gameOverPlayerCount;
bool isGameOver;	// 게임이 끝났는지 확인 하는 변수
bool isAllPlayerLogIn = false;	// 테스트 : true, 실제로는 false
int curPlayerCount = 0;
int tempMaxBettingCandy = 0;
int getPacketCount;
bool anotherBetWait;
int betCount;
bool isPlayerBet;
bool isPreferencePlayerDie;
int winnerPlayerIndex;

int GameManager::SelectMenu()
{
	int x = 45;
	int y = 14;
	ConsoleManager::Instance().GoToXY(x - 2, y);
	printf("> 게임시작");
	ConsoleManager::Instance().GoToXY(x, y + 1);
	printf("게임정보");
	ConsoleManager::Instance().GoToXY(x, y + 2);
	printf("나가기");
	while (true)
	{
		int _SelectMenu = InputManager::Instance().KeyBoardControl();
		switch (_SelectMenu)
		{
		case UP:
			if (y > 14)
			{
				ConsoleManager::Instance().GoToXY(x - 2, y);
				printf(" ");
				ConsoleManager::Instance().GoToXY(x - 2, --y);
				printf(">");
			}
			break;
		case DOWN:
			if (y < 16)
			{
				ConsoleManager::Instance().GoToXY(x - 2, y);
				printf(" ");
				ConsoleManager::Instance().GoToXY(x - 2, ++y);
				printf(">");
			}
			break;
		case SELECT:
			system("cls");
			return (y - 14);
			break;
		}
	}
}
void GameManager::SetCardNumber()
{
	for (int i = 0; i < 20; i++)
	{
		card[i].SetCardNumber(i + 1);
		card[i].cardIndex = i;
	}
}
void GameManager::HandOutCard()
{
	ConsoleManager::Instance().GoToXY(75, 50);
	cout << "패 돌리는 중................";
	int i = preferencePlayerIndex;
	do
	{
		if ((players[i].isDie == false) && (players[i].isGameOver == false))
		{
			if (i == player.index)
			{
				player.PlayerGetCard(card[cardIndex]);
				PrintManager::Instance().DrawPlayerCard(i, player.myCard[handOutIndex - 1].GetcardNumber());
			}
			players[i].PlayerGetCard(card[cardIndex++]);
			Sleep(500);
		}
		i = (i + 1) % 4;
	} while (i != preferencePlayerIndex);

	PrintManager::Instance().EraseArea(true, 75, 50, 102, 50);
}
void GameManager::MainGameLogic()
{
	ConsoleManager::Instance().CursorView();
	ConsoleManager::Instance().ChangeConsloePosition(450, 15);
	preferencePlayerIndex = 0;

	while (!isGameOver)
	{
		PrintManager::Instance().PrintGameTitle();
		int menuIndex = SelectMenu();
		if (menuIndex == 0)
		{
			PlayPressButton();
			// 게임시작
			system("cls");
			ConsoleManager::Instance().ChangeConsoleSize(200, 60);
			SetCardNumber();
			ConsoleManager::Instance().ChangeFont();

			PrintManager::Instance().DrawMainGameScreen(&player);
			
			GameStart();
		}
		else if (menuIndex == 1)
		{
			PlayPressButton();
			// 게임정보
			PrintManager::Instance().GameInfoDraw();
		}
		else if (menuIndex == 2)
		{
			PlayPressButton();
			// 종료
			return;
		}
		system("cls");
	}
}
void GameManager::MixCard(int* p_card)
{

	for (int i = 0; i < 20; i++)
	{
		card[i].SetCardNumber(p_card[i]);
	}
	/*srand(seed);
	int x = 0, y = 0, temp = 0, tempCardIndex = 0;
	Card cardX;
	Card cardY;
	for (int i = 0; i < 500; i++)
	{
		x = rand() % 20;
		y = rand() % 20;

		if (x != y)
		{
			cardX = card[x];
			cardY = card[y];

			temp = card[x].GetcardNumber();
			card[x].SetCardNumber(card[y].GetcardNumber());
			card[y].SetCardNumber(temp);

			tempCardIndex = cardX.cardIndex;
			cardX.cardIndex = cardY.cardIndex;
			cardY.cardIndex = tempCardIndex;

			card[x].cardIndex = cardY.cardIndex;
			card[y].cardIndex = cardX.cardIndex;
		}
	}*/
}
void GameManager::ClearInputBuffer()
{
	while (_kbhit()) _getch();
}
void GameManager::ParticipateCandy()
{
	int playerCount = 0;
	for (int i = 0; i < 4; i++)
	{
		if (players[i].candy - BASIC_GAME_MONEY < 0)
		{
			players[i].isGameOver = true;
			players[i].isDie = true;
			++diePlayerCount;
			if (i == player.index)
			{
				player.isGameOver = true;
				player.isDie = true;
			}
		}
		else
		{
			playerCount++;
			players[i].candy -= BASIC_GAME_MONEY;
			if (i == player.index)
			{
				player.candy -= BASIC_GAME_MONEY;
			}
		}
	}
	totalGameCandy += (BASIC_GAME_MONEY * playerCount);
}
bool GameManager::IsBettingAble(int needCandy)
{
	if (player.candy >= needCandy)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GameManager::UpdateTotalGameCandyAndFrontBetcandy(int playerIndex, int betInfo)
{
	int tempFrontPlayerBettingCand = 0;

	switch (betInfo)
	{
	case 4:
		break;
	case 5:
		totalGameCandy += (frontPlayerBettingCandy + BASIC_GAME_MONEY);
		frontPlayerBettingCandy = (frontPlayerBettingCandy + BASIC_GAME_MONEY);
		break;
	case 6:
		totalGameCandy += (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		break;
	case 7:
		frontPlayerBettingCandy = frontPlayerBettingCandy;
		totalGameCandy += (frontPlayerBettingCandy);
		break;
	case 8:
		tempFrontPlayerBettingCand = frontPlayerBettingCandy;
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (totalGameCandy / 4));
		totalGameCandy += (tempFrontPlayerBettingCand + (totalGameCandy / 4));
		break;
	case 9:
		tempFrontPlayerBettingCand = frontPlayerBettingCandy;
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (totalGameCandy / 2));
		totalGameCandy += (tempFrontPlayerBettingCand + (totalGameCandy / 2));
		break;
	}
}
void GameManager::UpdatePlayerBettingInfo(int playerIndex, int betInfo)
{
	int tempFrontPlayerBettingCandy = 0;

	switch (betInfo)
	{
	case 4: // 다이

		PlayDie();
		if (preferencePlayerIndex == playerIndex)
		{
			players[playerIndex].isCircuit = true;
			players[playerIndex].isPreference = false;

			for (int i = 1; i < 4; i++)
			{
				if (!players[(playerIndex + i) % 4].isDie)
				{
					preferencePlayerIndex = (playerIndex + i) % 4;
					players[preferencePlayerIndex].isPreference = true;
					
					break;
				}
			}
			players[playerIndex].isDie = true;
			if (player.index == playerIndex) player.isDie = true;
		}
		else
		{
			players[playerIndex].isCircuit = true;
			players[playerIndex].isDie = true;
			if (player.index == playerIndex) player.isDie = true;
		}

		break;
		case 5: // 삥
		{	
			PlayBbing();
			players[playerIndex].candy -= BASIC_GAME_MONEY;
		players[playerIndex].myBettingCandy += BASIC_GAME_MONEY;
		totalGameCandy += BASIC_GAME_MONEY;
		players[playerIndex].isCircuit = true;
		frontPlayerBettingCandy = BASIC_GAME_MONEY;

		break;
		}
		case 6:
		{
			PlayDdadang();
		players[playerIndex].candy -= (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		players[playerIndex].myBettingCandy += (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		players[playerIndex].isCircuit = true;
		totalGameCandy += (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (frontPlayerBettingCandy * 2));
		break;
		}
	case 7:	// 콜
		PlayCall();
		if (players[playerIndex].candy >= (maxBettingCandy - players[playerIndex].myBettingCandy))	// 판돈에서 내가 이전에 낸 금액을 뺀 돈을 베팅할 수 있으면 들어옴
		{
			totalGameCandy += (maxBettingCandy - players[playerIndex].myBettingCandy);
			players[playerIndex].candy -= (maxBettingCandy - players[playerIndex].myBettingCandy);
			players[playerIndex].myBettingCandy += (maxBettingCandy - players[playerIndex].myBettingCandy);
			players[playerIndex].isCircuit = true;
			players[playerIndex].isCall = true;
		}
		else
		{
			totalGameCandy += players[playerIndex].candy;
			players[playerIndex].candy -= players[playerIndex].candy;
			players[playerIndex].myBettingCandy += players[playerIndex].candy;
			players[playerIndex].isCall = true;
			players[playerIndex].isNoCandy = true;
			players[playerIndex].isCircuit = true;		}
		break;
	case 8:
		PlayQuarter();
		players[playerIndex].isCircuit = true;
		players[playerIndex].candy -= (frontPlayerBettingCandy + (totalGameCandy / 4));
		players[playerIndex].myBettingCandy += (frontPlayerBettingCandy + (totalGameCandy / 4));
		
		tempFrontPlayerBettingCandy = frontPlayerBettingCandy;
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (totalGameCandy / 4));
		totalGameCandy += (tempFrontPlayerBettingCandy + (totalGameCandy / 4));

		break;
	case 9:
		PlayHalf();
		player.isCircuit = true;
		players[playerIndex].isCircuit = true;		players[playerIndex].candy -= (frontPlayerBettingCandy + (totalGameCandy / 2));
		players[playerIndex].myBettingCandy += (frontPlayerBettingCandy + (totalGameCandy / 2));
		
		tempFrontPlayerBettingCandy = frontPlayerBettingCandy;
		frontPlayerBettingCandy = (frontPlayerBettingCandy + (totalGameCandy / 2));
		totalGameCandy += (tempFrontPlayerBettingCandy + (totalGameCandy / 2));
		break;
	}

	player = players[player.index];
}
void GameManager::GetOpenCardInfo(int playerIndex, int cardIndex)
{
	players[playerIndex].myOpenCard = card[cardIndex];
	getPacketCount++;
}
void GameManager::AllPlayerLogIn()
{
	isAllPlayerLogIn = true;

}
void GameManager::ShowAllPlayerMatchCard()
{
	for (int i = 0; i < 4; i++)
	{
		if (players[i].isDie || players[i].isGameOver) continue;
		switch (i)
		{
		case 0:
			PrintManager::Instance().PrintImage(CardArea::P1_1, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[0].cardNumber));
			PrintManager::Instance().PrintImage(CardArea::P1_2, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[1].cardNumber));
			break;

		case 1:
			PrintManager::Instance().PrintImage(CardArea::P2_1, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[0].cardNumber));
			PrintManager::Instance().PrintImage(CardArea::P2_2, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[1].cardNumber));
			break;

		case 2:
			PrintManager::Instance().PrintImage(CardArea::P3_1, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[0].cardNumber));
			PrintManager::Instance().PrintImage(CardArea::P3_2, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[1].cardNumber));
			break;

		case 3:
			PrintManager::Instance().PrintImage(CardArea::P4_1, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[0].cardNumber));
			PrintManager::Instance().PrintImage(CardArea::P4_2, PrintManager::Instance().GetDrawImage(players[i].mySelectCard[1].cardNumber));
			break;
		}
	}
}
void GameManager::CurrentLogInPlayerCandyPrint()
{
	for (int i = 0; i < curPlayerCount; i++)
	{
		switch (i)
		{
		case 0:
			// 플레이어1 캔디출력
			ConsoleManager::Instance().GoToXY(125, 14);
			std::cout << "Candy : " << players[0].candy;
			break;
		case 1:
			// 플레이어2 캔디출력
			ConsoleManager::Instance().GoToXY(125, 37);
			std::cout << "Candy : " << players[1].candy;
			break;
		case 2:
			// 플레이어3 캔디출력
			ConsoleManager::Instance().GoToXY(25, 14);
			std::cout << "Candy : " << players[2].candy;
			break;
		case 3:
			// 플레이어4 캔디출력
			ConsoleManager::Instance().GoToXY(25, 37);
			std::cout << "Candy : " << players[3].candy;
			break;
		case 4:
			break;
		}
	}
}
void GameManager::MatchCardSelect()
{
	if (player.isDie || player.isGameOver) return;

	ConsoleManager::Instance().GoToXY(75, 50);
	cout << "승부를 겨룰 카드 조합을 선택하세요.";

	int selectNumber = 0;
	selectNumber = InputManager::Instance().KeyBoardControlOneTwoThree();
	C2S::SendSelectCombination sendSelectCombination;
	switch (selectNumber)
	{
	case ONE:

		player.mySelectCard[0] = player.myCard[0];
		player.mySelectCard[1] = player.myCard[1];
		//player.isSelectMatchCard = true;
		//players[player.index].isSelectMatchCard = true;

		sendSelectCombination.cardIndex1 = player.mySelectCard[0].cardIndex;
		sendSelectCombination.cardIndex2 = player.mySelectCard[1].cardIndex;
		sendSelectCombination.id = player.id;
		sendSelectCombination.index = player.index;

		TCP_Client.SendToServer(&sendSelectCombination);
		break;
	case TWO:

		player.mySelectCard[0] = player.myCard[0];
		player.mySelectCard[1] = player.myCard[2];


		sendSelectCombination.cardIndex1 = player.mySelectCard[0].cardIndex;
		sendSelectCombination.cardIndex2 = player.mySelectCard[1].cardIndex;
		sendSelectCombination.id = player.id;
		sendSelectCombination.index = player.index;

		TCP_Client.SendToServer(&sendSelectCombination);
		break;
	case THREE:

		player.mySelectCard[0] = player.myCard[1];
		player.mySelectCard[1] = player.myCard[2];
		// player.isSelectMatchCard = true;
		// players[player.index].isSelectMatchCard = true;

		sendSelectCombination.cardIndex1 = player.mySelectCard[0].cardIndex;
		sendSelectCombination.cardIndex2 = player.mySelectCard[1].cardIndex;
		sendSelectCombination.id = player.id;
		sendSelectCombination.index = player.index;

		TCP_Client.SendToServer(&sendSelectCombination);
		break;
	}
	PrintManager::Instance().EraseArea(true, 75, 50, 109, 50);
}
void GameManager::UpdateMatchCardSelect(int cardIndex1, int cardIndex2, int playerIndex)
{
	players[playerIndex].mySelectCard[0] = card[cardIndex1];
	players[playerIndex].mySelectCard[1] = card[cardIndex2];
	players[playerIndex].isSelectMatchCard = true;
	if (playerIndex == player.index)
	{
		player.isSelectMatchCard = true;
	}
}
void GameManager::DecideWinnerPlayer(int winnerPlayerIndex)
{
	if (winnerPlayerIndex == 4) // 무승부가 있을 경우
	{
		int tempIndex = 0;
		int drawPlayerCount = 0;
		for (int i = 0; i < 4; i++)
		{
			if (players[i].myJokbo == JOKBO::DRAW)
			{
				tempIndex = i;
				drawPlayerCount++;
				if (i == 0)
				{
					PrintManager::Instance().PrintWin(1);
				}
				if (i == 1)
				{
					PrintManager::Instance().PrintWin(2);
				}
				if (i == 2)
				{
					PrintManager::Instance().PrintWin(3);
				}
				if (i == 3)
				{
					PrintManager::Instance().PrintWin(4);
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (players[i].myJokbo == JOKBO::DRAW)
			{

				if (players[i].isNoCandy)
				{
					players[i].isNoCandy = false;
				}
				if (i == players[i].index)
				{
					//player.candy += (totalGameCandy / drawPlayerCount);
					players[i].candy += (totalGameCandy / drawPlayerCount);
					//if (player.isNoCandy) player.isNoCandy = false;
					if (players[i].isNoCandy) players[i].isNoCandy = false;
				}
			}
			else
			{
				if (i == player.index)
				{
					if (player.isNoCandy)
					{
						if (!player.isGameOver)
						{
							player.isGameOver = true;
							players[i].isGameOver = true;
							++gameOverPlayerCount;
						}
					}
				}
			}
		}
		preferencePlayerIndex = tempIndex;
		winnerPlayerIndex = tempIndex;
		players[winnerPlayerIndex].isPreference = true;
		if (winnerPlayerIndex == player.index)
		{
			player.isPreference = true;
		}
		player = players[player.index];
		betCount = tempIndex;
	}
	else  // 이긴 사람이 1명인 경우
	{
		for (int i = 0; i < 4; i++)
		{
			if (i != winnerPlayerIndex)
			{
				if (players[i].isNoCandy)
				{
					players[i].isGameOver = true;
				}
				if (i == player.index && player.isNoCandy)
				{
					if (!player.isGameOver)
					{
						player.isGameOver = true;
						players[player.index].isGameOver = true;
						++gameOverPlayerCount;
					}
				}
			}
			if (i != winnerPlayerIndex && i == player.index)
			{
				players[i].isPreference = false;
				player.isPreference = false;
			}
		}
		players[winnerPlayerIndex].candy += totalGameCandy;
		players[winnerPlayerIndex].isPreference = true;
		if (player.index == winnerPlayerIndex)
		{
			player.isPreference = true;
		}
		if (players[winnerPlayerIndex].isNoCandy)
		{
			players[winnerPlayerIndex].isNoCandy = false;
			if (winnerPlayerIndex == player.index)
			{
				player.isNoCandy = false;
			}
		}
		if (winnerPlayerIndex == player.index)
		{
			player.candy += totalGameCandy;
		}
		preferencePlayerIndex = winnerPlayerIndex;
		winnerPlayerIndex = winnerPlayerIndex;
		betCount = winnerPlayerIndex;
		PrintManager::Instance().PrintWin(winnerPlayerIndex + 1);
	}
	if (gameOverPlayerCount == 3)
	{
		isGameOver = true;
		exit(0);
	}
}
bool GameManager::ResetGame()
{
	Card tempCard;
	tempCard.cardNumber = 0;
	handOutIndex = 1;
	cardIndex = 0;
	diePlayerCount = 0;
	callPlayerCount = 0;
	totalGameCandy = 0;
	isAllPlayerLogIn = false;
	player.cardIndex = 0;
	player.myOpenCard = tempCard;
	for (int i = 0; i < 4; i++)
	{
		players[i].isSelectMatchCard = false;
		players[i].myJokbo = JOKBO::YET;
		players[i].isDie = false;
		players[i].myBettingCandy = 0;
		players[i].isCall = false;
		players[i].isCircuit = false;
		players[i].cardIndex = 0;
		players[i].myOpenCard = tempCard;
		for (int j = 0; j < 3; j++)
		{
			players[i].myCard[j].SetCardNumber(-1);
		}
		for (int k = 0; k < 2; k++)
		{
			players[i].mySelectCard[k].SetCardNumber(-1);
		}
		if (i == player.index)
		{
			player.myJokbo = JOKBO::YET;
			player.isCall = false;
			player.isDie = false;
			player.isCircuit = false;
			player.myBettingCandy = 0;
			for (int j = 0; j < 3; j++)
			{
				player.myCard[j].SetCardNumber(-1);
			}
			for (int k = 0; k < 2; k++)
			{
				player.mySelectCard[k].SetCardNumber(-1);
			}
		}
	}

	system("cls");
	PrintManager::Instance().DrawMainGameScreen(&player);
	PrintManager::Instance().FirstAllPlayerCandyRePrint();	// 게임 총 캔디도 출력
	PrintManager::Instance().DeleteAllImage();
	PrintManager::Instance().PrintPlayerState(players);
	return true;
}
void GameManager::GameStart()
{
	TCP_Client.TCPClientStart();

	while (player.index < 0)
	{
		//서버에 연결되서 index 부여될때까지 대기
		Sleep(1);
	}

	// 메인 게임 루프
	while (true)
	{

		while (true)
		{
			// 4명이 접속 할 때까지 대기
			if (curPlayerCount >= 2)
			{
				break;
			}
			Sleep(1);
		}
		Sleep(500);

		// 0번 플레이어는 게임 시작 버튼 활성화
		if (player.index == preferencePlayerIndex)
		{
			ConsoleManager::Instance().GoToXY(75, 50);
			cout << "게임을 시작하려면 0번을 누르세요.";
			player.isPreference = true;
			players[player.index].isPreference = true;

			while (true)
			{
				char temp = _getch();
				if (temp == '0')
				{
					C2S::HostStartingGame hostStartingGame;
					hostStartingGame.id = player.id;
					hostStartingGame.index = player.index;
					TCP_Client.SendToServer(&hostStartingGame);
					break;
				}
			}
			PrintManager::Instance().EraseArea(true, 75, 50, 95, 50);
		}
		
		while (true)
		{
			// 0번이 아닌 플레이어는 게임 시작 대기
			// 서버에서 게임 시작 패킷을 받으면 탈출
			if (isAllPlayerLogIn)
			{
				break;
			}
			Sleep(1);
		}
		
		
		// 인원 다 모이면 게임 시작하는 함수
		frontPlayerBettingCandy = 0;
		ParticipateCandy();		// 참여 가능한지 확인하고 돈 계산했음
		std::system("cls");
		PrintManager::Instance().DrawMainGameScreen(&player);
		PrintManager::Instance().FirstAllPlayerCandyRePrint();	// 게임 총 캔디도 출력
		
		// 입장할 때 내가 몇번인지 출력함
		ConsoleManager::Instance().GoToXY(2, 55);
		std::cout << "My Player : " << "player" << player.index + 1;

		// 이제 시작
		Sleep(1000);

		//// 처음 1장 째 나눠주기
		HandOutCard();		// players배열에 나에 해당하는 인덱스 값 바꿨음, 다이를 눌렀거나 게임오버가 되면 패스
		//Sleep(200);


		//// 처음 2장 째 나눠주기
		HandOutCard();		// players배열에 나에 해당하는 인덱스 값 바꿨음, 다이를 눌렀거나 게임오버가 되면 패스

		InputManager::Instance().OpenCardInput();// 입력 함수			// players배열에 나에 해당하는 인덱스 값 바꿨음


		// 모든 플레이어가 카드 선택 끝나고 출력
		PrintManager::Instance().PrintAllPlayerOpenCard();


		// 첫 번째 베팅에서 전부 다이하면 다음게임
		if (InputManager::Instance().BettingInput(true))
			continue;


		player.isCircuit = false;
		player.isCall = false;

		for (int i = 0; i < 4; i++)
		{
			players[i].isCircuit = false;
			players[i].isCall = false;
		}

		isPreferencePlayerDie = false;

		betCount = preferencePlayerIndex;
		callPlayerCount = 0;

		frontPlayerBettingCandy = 0;
		////// 3번째 카드 나눠 주기
		HandOutCard();
		
		PrintManager::Instance().ShowCardCombination(player);

		// 두번째 베팅에서 전부 다이하면 담겜
		if (InputManager::Instance().BettingInput(false))
			continue;

		player.isCircuit = false;
		for (int i = 0; i < 4; i++)
		{
			players[i].isCircuit = false;
		}

		// 두번째 베팅 끝나고 카드조합 선택하기
		MatchCardSelect();

		// 플레이어들이 선택한 카드 조합 정보 출력하기
		PrintManager::Instance().PrintAllPlayerMatchCard();

		DecideWinnerPlayer(CompareJokbo(players));

		PlayMoneyGet();

		Sleep(4000);

		PrintManager::Instance().FirstAllPlayerCandyRePrint();

		SendPreferencePlayerEndGame();

		PrintManager::Instance().PrintPlayerState(players);

		ResetGame();
	}
}
void GameManager::SendPreferencePlayerEndGame()
{
	if (player.isPreference)
	{
		for(int i = 0 ; i < 4 ; ++i)
		{
			C2S::HostEndGame packet;
			packet.id = player.id;
			packet.playerIndex = players[i].index;
			packet.playerCandy = players[i].candy;
			
			TCP_Client.SendToServer(&packet);
		}
	}
}
GameManager& GameManager::Instance()
{
	static GameManager* GM = new GameManager();
	return *GM;
}