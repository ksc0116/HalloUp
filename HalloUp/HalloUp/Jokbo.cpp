#include "Jokbo.h"
#include "Player.h"

void JokboGubun(Player* player, int cardIndex1 = -1, int cardIndex2 = -1)
{
	int playerCard_1 = playerCard_1 = player->mySelectCard[0].GetcardNumber();
	int playerCard_2 = playerCard_2 = player->mySelectCard[1].GetcardNumber();

	if (cardIndex1 != -1)
	{
		playerCard_1 = player->myCard[cardIndex1].GetcardNumber();
		playerCard_2 = player->myCard[cardIndex2].GetcardNumber();
	}

	if (playerCard_1 % 10 > playerCard_2 % 10)
	{
		int temp = playerCard_2;
		playerCard_2 = playerCard_1;
		playerCard_1 = temp;
	}


	if (playerCard_1 == 13 && playerCard_2 == 18)		// 38±¤¶¯
	{
		player->myJokbo = GT38;
	}
	else if (playerCard_1 == 11 && playerCard_2 == 18)	// 18±¤¶¯
	{
		player->myJokbo = GT18;
	}
	else if (playerCard_1 == 11 && playerCard_2 == 13)	// 13±¤¶¯
	{
		player->myJokbo = GT13;
	}
	else if (playerCard_1 % 10 == playerCard_2 % 10)			// 1~9 ¶¯, Àå¶¯(10¶¯)
	{
		switch (playerCard_1)
		{
		case 1: case 11: player->myJokbo = TT1;
			break;

		case 2: case 12: player->myJokbo = TT2;
			break;

		case 3: case 13: player->myJokbo = TT3;
			break;

		case 4: case 14: player->myJokbo = TT4;
			break;

		case 5: case 15: player->myJokbo = TT5;
			break;

		case 6: case 16: player->myJokbo = TT6;
			break;

		case 7: case 17: player->myJokbo = TT7;
			break;

		case 8: case 18: player->myJokbo = TT8;
			break;

		case 9: case 19: player->myJokbo = TT9;
			break;

		case 10: case 20: player->myJokbo = ZTT;
			break;
		}
	}
	else
	{
		switch (playerCard_1)
		{
		case 1: case 11:
			if (playerCard_2 == 2 || playerCard_2 == 12) { player->myJokbo = ALI; }			// 1¿ù, 2¿ù : ¾Ë¸®
			else if (playerCard_2 == 4 || playerCard_2 == 14) { player->myJokbo = DS; }		// 1¿ù, 4¿ù : µ¶»ç
			else if (playerCard_2 == 9 || playerCard_2 == 19) { player->myJokbo = GBB; }		// 1¿ù, 9¿ù : ±¸»æ
			else if (playerCard_2 == 10 || playerCard_2 == 20) { player->myJokbo = ZBB; }	// 1¿ù, 10¿ù : Àå»æ
			break;
		case 3: case 13:
			if (playerCard_2 == 7 || playerCard_2 == 17) { player->myJokbo = TTJ; }			// 3¿ù, 7¿ù : ¶¯ÀâÀÌ
			break;
		case 4: case 14:
			if (playerCard_1 == 14 && playerCard_2 == 17) { player->myJokbo = AHOS; }		// 4¿­²ý, 7¿­²ý : ¾ÏÇà¾î»ç
			else if (playerCard_2 == 6 || playerCard_2 == 16) { player->myJokbo = SYG; }		// 4¿ù, 6¿ù : ¼¼·ú
			else if (playerCard_2 == 10 || playerCard_2 == 20) { player->myJokbo = ZBB; }	// 4¿ù, 10¿ù : Àå»ç			
			break;
		}
	}

	if (player->myJokbo == YET)
	{
		int playerCard = (playerCard_1 + playerCard_2) % 10;
		switch (playerCard)
		{
		case 1: player->myJokbo = KKT1;
			break;
		case 2: player->myJokbo = KKT2;
			break;
		case 3: player->myJokbo = KKT3;
			break;
		case 4: player->myJokbo = KKT4;
			break;
		case 5: player->myJokbo = KKT5;
			break;
		case 6: player->myJokbo = KKT6;
			break;
		case 7: player->myJokbo = KKT7;
			break;
		case 8: player->myJokbo = KKT8;
			break;
		case 9: player->myJokbo = KKT9;
			break;
		case 0: player->myJokbo = KKT0;
			break;
		}
	}
}

int WinnerPlayerGubun(Player* player)
{
	int winnerIndex = 0;
	bool isDraw = false;

	for (int i = 1; i < 4; i++)
	{
		if(player[winnerIndex].myJokbo == YET)
			continue;

		if (player[winnerIndex].myJokbo == TTJ || player[winnerIndex].myJokbo == AHOS)
		{
			if (player[winnerIndex].myBettingCandy == AHOS) { player[winnerIndex].myJokbo = KKT1; }
			if (player[winnerIndex].myBettingCandy == TTJ) { player[winnerIndex].myJokbo = KKT0; }

			for (int j = 0; j < 3; j++)
			{
				if (player[winnerIndex].myJokbo == KKT1)
				{
					if (player[j].myJokbo == GT13 || player[j].myJokbo == GT18)
					{
						player[winnerIndex].myJokbo = AHOS;
						break;
					}

				}
				else if (player[winnerIndex].myJokbo == KKT0)
				{
					if (player[j].myJokbo > 7 && player[j].myJokbo < 15)
					{
						player[winnerIndex].myJokbo = TTJ;
						break;
					}
				}
			}
			i = 0;
		}

		if (player[winnerIndex].myJokbo > player[i].myJokbo)
		{
			if (isDraw)
			{
				player[winnerIndex].myJokbo = DRAW;
				isDraw = false;
			}

			winnerIndex = i;
		}
		else if (player[winnerIndex].myJokbo == player[i].myJokbo)
		{
			player[i].myJokbo = DRAW;
			isDraw = true;
		}
	}

	if ((isDraw == true))
	{
		player[winnerIndex].myJokbo = DRAW;
		winnerIndex = 4;
	}

	return winnerIndex;
}

void JokboGubun(Player* player, JOKBO* jokbo)
{
	JokboGubun(player, 0, 1);
	jokbo[0] = player->myJokbo;
	player->myJokbo = YET;

	JokboGubun(player, 0, 2);
	jokbo[1] = player->myJokbo;
	player->myJokbo = YET;

	JokboGubun(player, 1, 2);
	jokbo[2] = player->myJokbo;
	player->myJokbo = YET;
}

int CompareJokbo(Player* player)
{
	for (int i = 0; i < 4; i++)
	{
		if (!player[i].isDie)
		{
			JokboGubun(&player[i]);
		}
	}

	return WinnerPlayerGubun(player);
}

