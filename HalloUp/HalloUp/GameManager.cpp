#include "GameManager.h"
#include "sound.h"

using namespace std;

TcpClient TCP_Client;
Player player;
Player players[4];
Card card[20];
int cardIndex = 0;		// ���� �������� �ʱ�ȭ �ʿ���
int handOutIndex = 1;	// ���� �������� �ʱ�ȭ �ʿ���
int totalGameCandy = 0;	// ���� �������� �ʱ�ȭ �ʿ���
int maxBettingCandy;	// ���� �ý����� ���� �� ���� �ʱ�ȭ �ʿ���
int frontPlayerBettingCandy;
int preferencePlayerIndex;
int tempPreferencePlayerIndex;
int diePlayerCount;		// ���� �������� �ʱ�ȭ �ʿ���
int callPlayerCount;
int gameOverPlayerCount;
bool isGameOver;	// ������ �������� Ȯ�� �ϴ� ����
bool isAllPlayerLogIn = false;	// �׽�Ʈ : true, �����δ� false
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
	printf("> ���ӽ���");
	ConsoleManager::Instance().GoToXY(x, y + 1);
	printf("��������");
	ConsoleManager::Instance().GoToXY(x, y + 2);
	printf("������");
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
	cout << "�� ������ ��................";
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
			// ���ӽ���
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
			// ��������
			PrintManager::Instance().GameInfoDraw();
		}
		else if (menuIndex == 2)
		{
			PlayPressButton();
			// ����
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
	case 4: // ����

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
		case 5: // ��
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
	case 7:	// ��
		PlayCall();
		if (players[playerIndex].candy >= (maxBettingCandy - players[playerIndex].myBettingCandy))	// �ǵ����� ���� ������ �� �ݾ��� �� ���� ������ �� ������ ����
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
			// �÷��̾�1 ĵ�����
			ConsoleManager::Instance().GoToXY(125, 14);
			std::cout << "Candy : " << players[0].candy;
			break;
		case 1:
			// �÷��̾�2 ĵ�����
			ConsoleManager::Instance().GoToXY(125, 37);
			std::cout << "Candy : " << players[1].candy;
			break;
		case 2:
			// �÷��̾�3 ĵ�����
			ConsoleManager::Instance().GoToXY(25, 14);
			std::cout << "Candy : " << players[2].candy;
			break;
		case 3:
			// �÷��̾�4 ĵ�����
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
	cout << "�ºθ� �ܷ� ī�� ������ �����ϼ���.";

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
	if (winnerPlayerIndex == 4) // ���ºΰ� ���� ���
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
	else  // �̱� ����� 1���� ���
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
	PrintManager::Instance().FirstAllPlayerCandyRePrint();	// ���� �� ĵ�� ���
	PrintManager::Instance().DeleteAllImage();
	PrintManager::Instance().PrintPlayerState(players);
	return true;
}
void GameManager::GameStart()
{
	TCP_Client.TCPClientStart();

	while (player.index < 0)
	{
		//������ ����Ǽ� index �ο��ɶ����� ���
		Sleep(1);
	}

	// ���� ���� ����
	while (true)
	{

		while (true)
		{
			// 4���� ���� �� ������ ���
			if (curPlayerCount >= 2)
			{
				break;
			}
			Sleep(1);
		}
		Sleep(500);

		// 0�� �÷��̾�� ���� ���� ��ư Ȱ��ȭ
		if (player.index == preferencePlayerIndex)
		{
			ConsoleManager::Instance().GoToXY(75, 50);
			cout << "������ �����Ϸ��� 0���� ��������.";
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
			// 0���� �ƴ� �÷��̾�� ���� ���� ���
			// �������� ���� ���� ��Ŷ�� ������ Ż��
			if (isAllPlayerLogIn)
			{
				break;
			}
			Sleep(1);
		}
		
		
		// �ο� �� ���̸� ���� �����ϴ� �Լ�
		frontPlayerBettingCandy = 0;
		ParticipateCandy();		// ���� �������� Ȯ���ϰ� �� �������
		std::system("cls");
		PrintManager::Instance().DrawMainGameScreen(&player);
		PrintManager::Instance().FirstAllPlayerCandyRePrint();	// ���� �� ĵ�� ���
		
		// ������ �� ���� ������� �����
		ConsoleManager::Instance().GoToXY(2, 55);
		std::cout << "My Player : " << "player" << player.index + 1;

		// ���� ����
		Sleep(1000);

		//// ó�� 1�� ° �����ֱ�
		HandOutCard();		// players�迭�� ���� �ش��ϴ� �ε��� �� �ٲ���, ���̸� �����ų� ���ӿ����� �Ǹ� �н�
		//Sleep(200);


		//// ó�� 2�� ° �����ֱ�
		HandOutCard();		// players�迭�� ���� �ش��ϴ� �ε��� �� �ٲ���, ���̸� �����ų� ���ӿ����� �Ǹ� �н�

		InputManager::Instance().OpenCardInput();// �Է� �Լ�			// players�迭�� ���� �ش��ϴ� �ε��� �� �ٲ���


		// ��� �÷��̾ ī�� ���� ������ ���
		PrintManager::Instance().PrintAllPlayerOpenCard();


		// ù ��° ���ÿ��� ���� �����ϸ� ��������
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
		////// 3��° ī�� ���� �ֱ�
		HandOutCard();
		
		PrintManager::Instance().ShowCardCombination(player);

		// �ι�° ���ÿ��� ���� �����ϸ� ���
		if (InputManager::Instance().BettingInput(false))
			continue;

		player.isCircuit = false;
		for (int i = 0; i < 4; i++)
		{
			players[i].isCircuit = false;
		}

		// �ι�° ���� ������ ī������ �����ϱ�
		MatchCardSelect();

		// �÷��̾���� ������ ī�� ���� ���� ����ϱ�
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