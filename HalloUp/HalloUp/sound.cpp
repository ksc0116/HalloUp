#include "sound.h"

#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <chrono>
#include <thread>
#pragma comment(lib, "winmm.lib")

//실제로 프로젝트->속성->링커->입력에서 winmm.lib외부종속성으로 추가해야 한다!
using namespace std;

void PlayShuffle()
{
	PlaySound(TEXT("CardShuffle.wav"), NULL, SND_ASYNC);
}

void PlayMoneyGet()
{
	PlaySound(TEXT("CashRegister.wav"), NULL, SND_ASYNC);
}

void PlayMoneyLost()
{
	PlaySound(TEXT("LostMoney.wav"), NULL, SND_ASYNC);
}

void PlayGameOver()
{
	PlaySound(TEXT("GameOver.wav"), NULL, SND_ASYNC);
}

void PlayCardFlip()
{
	PlaySound(TEXT("CardFlip.wav"), NULL, SND_ASYNC);
}

void PlayDrumFill()
{
	PlaySound(TEXT("DrumFill.wav"), NULL, SND_ASYNC);
}

void PlayNextPlayer()
{
	PlaySound(TEXT("MildStart.wav"), NULL, SND_ASYNC);
}

void PlayNextGame()
{
	PlaySound(TEXT("NextGame.wav"), NULL, SND_ASYNC);
}

void PlayPressButton()
{
	PlaySound(TEXT("PressButton.wav"), NULL, SND_ASYNC);
}

void PlayTimerFive()
{
	PlaySound(TEXT("TickingTimerFive.wav"), NULL, SND_ASYNC);
}

void PlayTimerTen()
{
	PlaySound(TEXT("TickingTimerTen.wav"), NULL, SND_ASYNC);
}

void PlayDie()
{
	PlaySound(TEXT("V_DIE.wav"), NULL, SND_ASYNC);
}

void PlayQuarter()
{
	PlaySound(TEXT("V_QUARTER.wav"), NULL, SND_ASYNC);
}

void PlayHalf()
{
	PlaySound(TEXT("V_HALF.wav"), NULL, SND_ASYNC);
}

void PlayDdadang()
{
	PlaySound(TEXT("V_DDADANG.wav"), NULL, SND_ASYNC);
}

void PlayCall()
{
	PlaySound(TEXT("V_CALL.wav"), NULL, SND_ASYNC);

}

void PlayBbing()
{
	PlaySound(TEXT("V_BBING.wav"), NULL, SND_ASYNC);
}


