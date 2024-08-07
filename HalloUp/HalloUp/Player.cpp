#include "Player.h"

Player::Player()
{
	for (int i = 0; i < 3; i++)
	{
		myCard[i].SetCardNumber(-1);
	}
	for (int j = 0; j < 2; j++)
	{
		mySelectCard[j].SetCardNumber(-1);
	}
	cardIndex = 0;
	myJokbo = JOKBO::YET;
	isDie = false;
	isNoCandy = false;
	isGameOver = false;
}
void Player::PlayerGetCard(Card card)
{
	myCard[cardIndex++] = card;
	if (cardIndex >= 3)
	{
		cardIndex = 0;
	}
}