#include "InputManager.h"
#include "GameManager.h"
#include "ConsoleManager.h"
#include "PrintManager.h"
#include <iostream>
using namespace std;

InputManager& InputManager::Instance()
{
	static InputManager* IM = new InputManager();
	return *IM;
}
void InputManager::OpenCardInput()
{
	if (player.isGameOver)
		return;
	ConsoleManager::Instance().GoToXY(75, 50);
	cout << "오픈 할 카드를 선택해 주세요.";
	int selectNumber = KeyBoardControlOneTwo();
	switch (selectNumber)
	{
		case ONE:
			//PrintImage(tempArea, GetDrawImage(player.myCard[0].GetcardNumber()));
			player.myOpenCard = player.myCard[0];
			players[player.index].myOpenCard = player.myCard[0];
			break;
		case TWO:
			//PrintImage(tempArea, GetDrawImage(player.myCard[1].GetcardNumber()));
			player.myOpenCard = player.myCard[1];
			players[player.index].myOpenCard = player.myCard[1];
			break;
	}
	// 서버에 내가 선택한 카드 정보와 내 정보 보내기
	C2S::SendOpeningCard sendOpeningCard;
	sendOpeningCard.cardIndex = player.myOpenCard.cardIndex;
	sendOpeningCard.id = player.id;
	sendOpeningCard.index = player.index;
	TCP_Client.SendToServer(&sendOpeningCard);
	//=========================================================
	PrintManager::Instance().EraseArea(true, 75, 50, 104, 50);
}
int InputManager::KeyBoardControlOneTwo()
{
	GameManager::Instance().ClearInputBuffer();
	char temp;
	while (true)
	{
		temp = _getch();
		if (temp == '1') return ONE;
		else if (temp == '2') return TWO;
	}
}
int InputManager::KeyBoardControlOneTwoThree()
{
	GameManager::Instance().ClearInputBuffer();
	char temp;
	while (true)
	{
		temp = _getch();
		if (temp == '1') return ONE;
		else if (temp == '2') return TWO;
		else if (temp == '3') return THREE;
	}
}
int InputManager::KeyBoardControlBettingSystem()
{
	GameManager::Instance().ClearInputBuffer();

	// 미리 돈 계산 끝내서 버튼 지우기
	// 삥( 맨 처음 사람만 가능 )
	// 따당
	// 하프
	// 쿼터
	bool isBbing = true;
	bool isDD = true;
	bool isHalf = true;
	bool isQuarter = true;
	bool isCall = true;

	if ((player.candy < BASIC_GAME_MONEY) || (!player.isPreference) || (player.isPreference && player.isCircuit)) isBbing = false;
	if ((player.candy < ((frontPlayerBettingCandy)+(frontPlayerBettingCandy * 2))) || (player.isPreference && !player.isCircuit) || player.isCall) isDD = false;
	if ((player.candy < (frontPlayerBettingCandy + (totalGameCandy / 2))) || player.isCall) isHalf = false;
	if ((player.candy < (frontPlayerBettingCandy + (totalGameCandy / 4))) || player.isCall) isQuarter = false;
	if (player.isPreference && !player.isCircuit) isCall = false;

	PrintManager::Instance().DeleteSpecificBettingButton(isBbing, isDD, isCall,isQuarter, isHalf);
	// 4. 다이
	// 5. 삥
	// 6. 따당
	// 7. 콜
	// 8. 쿼터
	// 9. 하프

	char temp;
	while (true)
	{
		temp = _getch();
		if (player.isPreference && !player.isCircuit)
		{
			if (temp == '4') return FOUR;
			else if (temp == '5' && isBbing == true && !player.isCall) return FIVE;
			else if (temp == '8' && isQuarter == true && !player.isCall) return EIGHT;
			else if (temp == '9' && isHalf == true && !player.isCall) return NINE;
		}
		else if ((player.isPreference && player.isCircuit) || (player.isPreference == false))
		{
			if (temp == '4') return FOUR;
			else if (temp == '6' && isDD == true && !player.isCall) return SIX;
			else if (temp == '7') return SEVEN;
			else if (temp == '8' && isQuarter == true && !player.isCall) return EIGHT;
			else if (temp == '9' && isHalf == true && !player.isCall) return NINE;
		}
	}
}
bool InputManager::BettingInput(bool isFirst)
{

	while ((callPlayerCount + diePlayerCount) != 3)
	{
		anotherBetWait = true;
		if (!players[betCount].isDie && !players[betCount].isNoCandy && !players[betCount].isGameOver)
		{
			PrintManager::Instance().PrintArrow(players[betCount].index);
		}
		if (players[betCount].isDie || players[betCount].isNoCandy || players[betCount].isGameOver)
		{
			if (!(players[betCount].isDie) && players[betCount].candy == 0)
				++callPlayerCount;
			// 죽었으면 다음순서
			
			++betCount;
			anotherBetWait = false;
		}
		else if (player.index == betCount )
		{
			if(callPlayerCount + diePlayerCount == 3)
				anotherBetWait = false;
			else
			{
				ConsoleManager::Instance().GoToXY(75, 50);
				cout << "베팅을 시작해주세요.";

				PrintManager::Instance().PrintArrow(player.index);

				switch (KeyBoardControlBettingSystem())
				{

				case FOUR:	// 다이 // 지불 할 돈 없음
				{
					PrintManager::Instance().DeleteAllBettingButton();
					C2S::SendFirstBet packe4t;
					packe4t.betIndex = 4;
					packe4t.id = player.id;
					packe4t.index = player.index;
					TCP_Client.SendToServer(&packe4t);
					break;
				}
				case FIVE:	// 삥
				{
					C2S::SendFirstBet packet;
					packet.betIndex = 5;
					packet.id = player.id;
					packet.index = player.index;
					TCP_Client.SendToServer(&packet);
					break;
				}
				case SIX:	// 따당
				{
					C2S::SendFirstBet sendFirstBet;
					sendFirstBet.betIndex = 6;
					sendFirstBet.id = player.id;
					sendFirstBet.index = player.index;
					TCP_Client.SendToServer(&sendFirstBet);

					break;
				}
				case SEVEN:	// 콜
				{
					C2S::SendFirstBet sendFirstBet;
					sendFirstBet.betIndex = 7;
					sendFirstBet.id = player.id;
					sendFirstBet.index = player.index;
					TCP_Client.SendToServer(&sendFirstBet);
					break;
				}
				case EIGHT:	// 쿼터
				{
					C2S::SendFirstBet sendFirstBet;
					sendFirstBet.betIndex = 8;
					sendFirstBet.id = player.id;
					sendFirstBet.index = player.index;
					TCP_Client.SendToServer(&sendFirstBet);

					break;
				}
				case NINE:	// 하프
				{
					C2S::SendFirstBet sendFirstBet;
					sendFirstBet.betIndex = 9;
					sendFirstBet.id = player.id;
					sendFirstBet.index = player.index;
					TCP_Client.SendToServer(&sendFirstBet);
					break;
				}
				}
			}
		}

		while (anotherBetWait)
		{
			Sleep(1);
		}
		betCount %= 4;

		diePlayerCount = 0;
		for (auto a : players)
		{
			if (a.isDie)
				diePlayerCount++;
		}
		if ((diePlayerCount) == 3)
		{
			PlayMoneyGet();
			for (int i = 0; i < 4; i++)
			{
				if (!players[i].isDie && !players[i].isGameOver)
				{
					GameManager::Instance().DecideWinnerPlayer(i);
					break;
				}
			}
			Sleep(4000);
			PrintManager::Instance().FirstAllPlayerCandyRePrint();

			GameManager::Instance().SendPreferencePlayerEndGame();

			GameManager::Instance().ResetGame();
			return true;
		}
	}
	PrintManager::Instance().DeleteBettingInfo();
	return false;
}
int InputManager::KeyBoardControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{
		return SELECT;
	}
}