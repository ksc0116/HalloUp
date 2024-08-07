#include "Graphics.h"
#include "GameManager.h"
using namespace std;

//char _winMessage[20][40] =
//{
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','8','0','0','0','8','0','8','0','8','0','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','8','0','8','0','8','0','8','0','8','8','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','8','0','8','0','8','0','8','0','8','0','8','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','8','0','8','0','8','0','8','0','8','0','0','8','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','0','8','0','8','0','0','8','0','8','0','0','0','8','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'}
//};
//
/////여기부터 추가합니다!
//
//char _dieMessage[20][40] =
//{
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','0','8','8','8','8','0','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','8','8','8','8','8','8','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','8','8','0','0','8','8','8','0','0','8','8','8','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','8','8','0','0','8','8','0','0','0','0','8','8','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','8','8','0','0','0','0','8','8','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','0','0','0','0','0','0','0','0','8','8','0','0','0','0','8','8','8','0','0','8','8','8','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','8','8','8','8','8','8','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','8','8','8','8','8','8','8','8','0','0','8','8','0','0','0','0','0','0','8','8','8','8','0','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','8','0','0','0','9','9','9'},
//{'9','9','9','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'},
//{'9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9','9'}
//};
//
//char _bbingMessage[9][30] =
//{
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','2','2','2','2','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','2','0','2','0','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','2','2','2','2','2','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
//
//};
//
//
//char _ddaDangMessage[9][30] =
//{
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','c','c','c','c','c','0','0','c','c','c','c','c','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','c','0','c','0','0','0','0','c','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','c','c','c','c','c','0','0','c','c','c','c','c','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
//};
//
//char _callMessage[9][30] =
//{
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
//};
//
//char _quarterMessage[9][30] =
//{
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','7','7','7','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','7','7','7','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','7','0','0','7','7','7','7','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
//};
//
//char _halfMessage[9][30] =
//{
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','6','6','6','6','6','0','0','6','6','6','6','6','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','6','6','6','0','0','0','0','6','0','6','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','6','0','6','0','0','0','0','6','0','6','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','6','6','6','0','0','0','6','6','6','6','6','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
//{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
//
//};


///추가 부분 A 끝났습니다.


//Color 모듈을 통해서 enum 연결을 해놓았으나, 일단은 색변경을 0-15까지의 숫자로 받음. graphics.cpp의 Color 열거형 참조, 숫자 연동.


//텍스트의 배경/글자 색깔을 리셋시킨다.
//void ResetTextColor()
//{
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | 0);
//}

//void AddDecoration()
//{
//	ConsoleManager::Instance().GoToXY(0, 52);
//	DrawRow(0, 0, 100);
//
//	ConsoleManager::Instance().GoToXY(199, 79);
//}

//void PrintImage(CardArea _area, char _arr[][20])
//{
//	int _x = 0;
//	int _y = 0;
//	if (_area == CardArea::MAIN1)
//	{
//		_x = 48;
//		_y = 60;
//	}
//	else if (_area == CardArea::MAIN2)
//	{
//		_x = 78;
//		_y = 60;
//	}
//	else if (_area == CardArea::MAIN3)
//	{
//		_x = 108;
//		_y = 60;
//	}
//	else if (_area == CardArea::P1_1)
//	{
//		_x = 141;
//		_y = 5;
//	}
//	else if (_area == CardArea::P1_2)
//	{
//		_x = 166;
//		_y = 5;
//	}
//	else if (_area == CardArea::P2_1)
//	{
//		_x = 141;
//		_y = 28;
//	}
//	else if (_area == CardArea::P2_2)
//	{
//		_x = 166;
//		_y = 28;
//	}
//	else if (_area == CardArea::P3_1)
//	{
//		_x = 42;
//		_y = 5;
//	}
//	else if (_area == CardArea::P3_2)
//	{
//		_x = 66;
//		_y = 5;
//	}
//	else if (_area == CardArea::P4_1)
//	{
//		_x = 42;
//		_y = 28;
//	}
//	else if (_area == CardArea::P4_2)
//	{
//		_x = 66;
//		_y = 28;
//	}
//	else
//	{
//		cout << "wrong parameter";
//	}
//	ConsoleManager::Instance().GoToXY(_x, _y);
//	//전체 20, 인덱스는 -1
//	for (int i = 0; i < 19; i++)
//	{
//		for (int j = 0; j < 19; j++)
//		{
//			if (_arr[i][j] == '1')
//			{
//				ConsoleManager::Instance().SetColor(WHITE, WHITE);
//				cout << " ";
//			}
//			else if (_arr[i][j] == '0')
//			{
//				ConsoleManager::Instance().SetColor(BLACK, BLACK);
//				cout << " ";
//			}
//			else if (_arr[i][j] == '2')
//			{
//				ConsoleManager::Instance().SetColor(DARKYELLOW, DARKYELLOW);
//				cout << " ";
//			}
//			else if (_arr[i][j] == '3')
//			{
//				ConsoleManager::Instance().SetColor(RED, RED);
//				cout << " ";
//			}
//			else if (_arr[i][j] == '4')
//			{
//				ConsoleManager::Instance().SetColor(YELLOW, YELLOW);
//				cout << " ";
//			}
//			else if (_arr[i][j] == '5')
//			{
//				ConsoleManager::Instance().SetColor(PURPLE, PURPLE);
//				cout << " ";
//			}
//			//cout << smallGhost[i][j];
//		}
//		ConsoleManager::Instance().GoToXY(_x, _y + i);
//	}
//	ResetTextColor();
//	ConsoleManager::Instance().GoToXY(199, 79);
//}

//void PrintInfo(InfoArea _area, string _str)
//{
//	if (_area == InfoArea::INFO1)
//	{
//		ConsoleManager::Instance().GoToXY(4, 60);
//		cout << _str;
//	}
//	else if (_area == InfoArea::INFO2)
//	{
//		ConsoleManager::Instance().GoToXY(4, 67);
//		cout << _str;
//	}
//	else if (_area == InfoArea::INFO3)
//	{
//		ConsoleManager::Instance().GoToXY(4, 74);
//		cout << _str;
//	}
//	else
//	{
//		cout << "wrong parameter";
//	}
//	ConsoleManager::Instance().GoToXY(199, 79);
//}

//void FillArea(bool _isShort, int _startX, int _startY, int _endX, int _endY)
//{
//	if (_isShort)
//	{//일반 문자, 1칸의 크기를 가진 공간을 채운다.
//		int tempX = _startX;
//		int tempY = _startY;
//		ConsoleManager::Instance().GoToXY(tempX, tempY);
//		for (int i = tempY; i <= _endY; i++)
//		{
//			for (int j = tempX; j <= _endX; j++)
//			{
//				printf("0");
//			}
//			tempY++;
//			ConsoleManager::Instance().GoToXY(tempX, tempY);
//		}
//	}
//	else
//	{//일반 문자, 2칸의 크기를 가진 공간을 채운다.
//		int tempX = _startX;
//		int tempY = _startY;
//		ConsoleManager::Instance().GoToXY(tempX, tempY);
//		for (int i = 0; i <= (_endY - _startY); i++)
//		{
//			for (int j = 0; j <= (_endX - _startX) / 2; j++)
//			{
//				printf("■");
//			}
//			ConsoleManager::Instance().GoToXY(tempX, tempY + i);
//		}
//	}
//}

//void EraseArea(bool _isShort, int _startX, int _startY, int _endX, int _endY)
//{
//	if (_startY == _endY)
//	{
//		ConsoleManager::Instance().GoToXY(_startX, _startY);
//		for (int i = _startX; i <= _endX; i++)
//		{
//			printf(" ");
//		}
//	}
//	else
//	{
//		if (_isShort)
//		{
//			//일반 문자, 1칸의 크기를 가진 공간을 지운다.
//			int tempX = _startX;
//			int tempY = _startY;
//			ConsoleManager::Instance().GoToXY(tempX, tempY);
//			for (int i = tempY; i <= _endY; i++)
//			{
//				for (int j = tempX; j <= _endX; j++)
//				{
//					printf(" ");
//				}
//				tempY++;
//				ConsoleManager::Instance().GoToXY(tempX, tempY);
//			}
//		}
//		else
//		{
//			//일반 문자, 2칸의 크기를 가진 공간을 지운다.
//			int tempX = _startX;
//			int tempY = _startY;
//			ConsoleManager::Instance().GoToXY(tempX, tempY);
//			for (int i = 0; i <= (_endY - _startY); i++)
//			{
//				for (int j = 0; j <= (_endX - _startX) / 2; j++)
//				{
//					printf("  ");
//				}
//				ConsoleManager::Instance().GoToXY(tempX, tempY + i);
//			}
//		}
//	}
//	
//}

//void EraseArea(InfoArea _area)
//{
//	int _startX, _startY, _endX, _endY;
//
//	if (_area == InfoArea::INFO1)
//	{
//		_startX = 4;
//		_startY = 60;
//
//	}
//	else if (_area == InfoArea::INFO2)
//	{
//		_startX = 4;
//		_startY = 67;
//	}
//	else if (_area == InfoArea::INFO3)
//	{
//		_startX = 4;
//		_startY = 74;
//	}
//	_endX = _startX + 26;
//	_endY = _startY + 3;
//	//일반 문자, 2칸의 크기를 가진 공간을 지운다.
//	ConsoleManager::Instance().GoToXY(_startX, _startY);
//	for (int i = 0; i <= (_endY - _startY); i++)
//	{
//		for (int j = 0; j <= (_endX - _startX) / 2; j++)
//		{
//			printf("  ");
//		}
//		ConsoleManager::Instance().GoToXY(_startX, _startY + i);
//	}
//	ConsoleManager::Instance().GoToXY(199, 79);
//}

//void EraseArea(CardArea _area)
//{
//	int _startX, _startY, _endX, _endY;
//	if (_area == CardArea::MAIN1)
//	{
//		_startX = 48;
//		_startY = 60;
//	}
//	else if (_area == CardArea::MAIN2)
//	{
//		_startX = 78;
//		_startY = 60;
//	}
//	else if (_area == CardArea::MAIN3)
//	{
//		_startX = 108;
//		_startY = 60;
//	}
//	else if (_area == CardArea::P1_1)
//	{
//		_startX = 141;
//		_startY = 5;
//	}
//	else if (_area == CardArea::P1_2)
//	{
//		_startX = 166;
//		_startY = 5;
//	}
//	else if (_area == CardArea::P2_1)
//	{
//		_startX = 141;
//		_startY = 28;
//	}
//	else if (_area == CardArea::P2_2)
//	{
//		_startX = 166;
//		_startY = 28;
//	}
//	else if (_area == CardArea::P3_1)
//	{
//		_startX = 42;
//		_startY = 5;
//	}
//	else if (_area == CardArea::P3_2)
//	{
//		_startX = 66;
//		_startY = 5;
//	}
//	else if (_area == CardArea::P4_1)
//	{
//		_startX = 42;
//		_startY = 28;
//	}
//	else if (_area == CardArea::P4_2)
//	{
//		_startX = 66;
//		_startY = 28;
//	}
//
//	_endX = _startX + 19;
//	_endY = _startY + 18;
//	//일반 문자, 2칸의 크기를 가진 공간을 지운다.
//	ConsoleManager::Instance().GoToXY(_startX, _startY);
//	for (int i = 0; i <= (_endY - _startY); i++)
//	{
//		for (int j = 0; j <= (_endX - _startX) / 2; j++)
//		{
//			printf("  ");
//		}
//		ConsoleManager::Instance().GoToXY(_startX, _startY + i);
//	}
//	ConsoleManager::Instance().GoToXY(199, 79);
//}


//매개변수는 플레이어의 번호. 'WIN'을 해당 위치에 출력합니다.
//void PrintWin(int playerNo)
//{
//	int _x = -1, _y = -1;
//	int* p_x = &_x;
//	int* p_y = &_y;
//	switch (playerNo)
//	{
//		case 1:
//			*p_x = 103; // +3 +5
//			*p_y = 11;
//			break;
//		case 2:
//			*p_x = 103;
//			*p_y = 34;
//			break;
//		case 3:
//			*p_x = 4;
//			*p_y = 11;
//			break;
//		case 4:
//			*p_x = 4;
//			*p_y = 34;
//			break;
//		default:
//			cout << "wrong parameter";
//			break;
//	}
//	ConsoleManager::Instance().GoToXY(_x, _y);
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 17; j++)
//		{
//			if (_winMessage[i][j] == '0')
//			{
//				ConsoleManager::Instance().SetColor(WHITE, WHITE);
//				cout << " ";
//			}
//			else if (_winMessage[i][j] == '8')
//			{
//				ConsoleManager::Instance().SetColor(RED, RED);
//				cout << " ";
//			}
//			else if (_winMessage[i][j] == '9')
//			{
//				ConsoleManager::Instance().SetColor(YELLOW, YELLOW);
//				cout << " ";
//			}
//		}
//		ConsoleManager::Instance().GoToXY(_x, _y + i);
//	}
//	ResetTextColor();
//}



//(가로) X,Y는 시작 점. length는 길이.
//void DrawRow(int _x, int _y, int length)
//{
//	for (int i = 0; i < length; i++)
//	{
//		cout << "〓";
//	}
//}

//(세로) X,Y는 시작 점. length는 길이.
//void DrawColumn(int _x, int _y, int length)
//{
//	int localX = _x;
//	int localY = _y;
//	for (int i = 0; i < length; i++)
//	{
//		ConsoleManager::Instance().GoToXY(localX, localY);
//		cout << "∥";
//		localY += 1;
//	}
//}

//매개변수에 1: 플레이어1의 차례.. 이 방식대로 적을 수 있다!
//void DrawPlayerArrow(int playerNo) //매개변수 int = 플레이어 번호
//{
//	switch (playerNo)
//	{
//	case 1:
//		////player1
//
//		ConsoleManager::Instance().GoToXY(131, 10);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 9);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 7);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 6);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 5);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(127, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(129, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(133, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(135, 8);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(129, 9);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(132, 9);
//		cout << "■";
//		//FillArea(false,114, 10, 124, 20);
//		break;
//	case 2:
//		//player2
//		ConsoleManager::Instance().GoToXY(131, 33);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 32);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 30);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 29);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(131, 28);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(129, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(127, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(133, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(135, 31);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(129, 32);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(132, 32);
//		cout << "■";
//		break;
//	case 3:
//		////player3
//		ConsoleManager::Instance().GoToXY(31, 10);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 9);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 7);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 6);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 5);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(27, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(29, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(33, 8);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(35, 8);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(29, 9);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(32, 9);
//		cout << "■";
//
//		break;
//	case 4:
//		////player4
//		ConsoleManager::Instance().GoToXY(31, 33);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 32);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 30);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 29);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(31, 28);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(29, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(27, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(33, 31);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(35, 31);
//		cout << "■";
//
//		ConsoleManager::Instance().GoToXY(29, 32);
//		cout << "■";
//		ConsoleManager::Instance().GoToXY(32, 32);
//		cout << "■";
//		break;
//	default:
//		cout << "wrong parameter";
//		break;
//	}
//}

//매개변수(플레이어 번호)에 따라, 해당 칸에서 플레이어 턴임을 보여주는 칸을 없앤다. 
//void ErasePlayerArrow(int playerNo)
//{
//	switch (playerNo)
//	{
//	case 1:
//		////player1
//		EraseArea(false, 127, 5, 135, 11);
//		break;
//	case 2:
//		//player2
//		EraseArea(false, 127, 28, 135, 34);
//		break;
//	case 3:
//		////player3
//		EraseArea(false, 27, 5, 35, 11);
//		break;
//	case 4:
//		////player4
//		EraseArea(false, 27, 28, 35, 34);
//		break;
//	default:
//		cout << "wrong parameter";
//		break;
//	}
//}

//void DrawPlayerCardsOnBoard(int playerNo)
//{
//	switch (playerNo)
//	{
//	case 1:
//		ConsoleManager::Instance().GoToXY(129, 12); //y를 -2
//		cout << "player1";
//
//		ConsoleManager::Instance().GoToXY(139, 4); //y를 -2
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(139, 5, 18); //y를 -2
//		ConsoleManager::Instance().GoToXY(160, 4);
//		cout << "▧";
//		DrawColumn(161, 5, 18);//y를 -2
//		ConsoleManager::Instance().GoToXY(160, 23);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(139, 23);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//
//		ConsoleManager::Instance().GoToXY(165, 4);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(165, 5, 18);
//		ConsoleManager::Instance().GoToXY(185, 4);
//		cout << "▧";
//		DrawColumn(185, 5, 18);
//		ConsoleManager::Instance().GoToXY(185, 23);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(165, 23);
//		cout << "▨";
//		DrawRow(0, 0, 9);
//
//		break;
//	case 2:
//		ConsoleManager::Instance().GoToXY(129, 35);
//		cout << "player2";
//
//		ConsoleManager::Instance().GoToXY(139, 27);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(139, 28, 18);
//		ConsoleManager::Instance().GoToXY(160, 27);
//		cout << "▧";
//		DrawColumn(161, 28, 18);
//		ConsoleManager::Instance().GoToXY(161, 46);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(139, 46);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//
//		ConsoleManager::Instance().GoToXY(165, 27);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(165, 28, 18);
//		ConsoleManager::Instance().GoToXY(185, 27);
//		cout << "▧";
//		DrawColumn(185, 28, 18);
//		ConsoleManager::Instance().GoToXY(165, 46);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		ConsoleManager::Instance().GoToXY(185, 46);
//		cout << "▨";
//
//		break;
//	case 3:
//		ConsoleManager::Instance().GoToXY(29, 12);
//		cout << "player3";
//
//		ConsoleManager::Instance().GoToXY(39, 4);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(39, 5, 18);
//		ConsoleManager::Instance().GoToXY(60, 4);
//		cout << "▧";
//		DrawColumn(61, 5, 18);
//		ConsoleManager::Instance().GoToXY(60, 23);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(39, 23);
//		cout << "▧";
//		DrawRow(0, 0, 10);
//
//		ConsoleManager::Instance().GoToXY(65, 4);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(65, 5, 18);
//		ConsoleManager::Instance().GoToXY(86, 4);
//		cout << "▧";
//		DrawColumn(87, 5, 18);
//		ConsoleManager::Instance().GoToXY(86, 23);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(65, 23);
//		cout << "▧";
//		DrawRow(0, 0, 10);
//		break;
//	case 4:
//		ConsoleManager::Instance().GoToXY(29, 35);
//		cout << "player4";
//
//		ConsoleManager::Instance().GoToXY(39, 27);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(39, 28, 18);
//		ConsoleManager::Instance().GoToXY(60, 27);
//		cout << "▧";
//		DrawColumn(61, 28, 18);
//		ConsoleManager::Instance().GoToXY(60, 46);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(39, 46);
//		cout << "▧";
//		DrawRow(0, 0, 10);
//
//		ConsoleManager::Instance().GoToXY(65, 27);
//		cout << "▨";
//		DrawRow(0, 0, 10);
//		DrawColumn(65, 28, 18);
//		ConsoleManager::Instance().GoToXY(86, 27);
//		cout << "▧";
//		DrawColumn(87, 28, 18);
//		ConsoleManager::Instance().GoToXY(86, 46);
//		cout << "▨";
//		ConsoleManager::Instance().GoToXY(65, 46);
//		cout << "▧";
//		DrawRow(0, 0, 10);
//		break;
//	default:
//		cout << "wrong parameter";
//		break;
//	}
//}

//void PutCardFrames()
//{
//	ConsoleManager::Instance().GoToXY(45, 59); //기존에서 y에서 1을 뺌
//	cout << "▨";
//	DrawRow(0, 0, 11);
//	DrawColumn(45, 60, 18); //기존에서 y에서 1을 뺌, 길이 18로
//	ConsoleManager::Instance().GoToXY(45, 78); //y에 1추가.
//	cout << "▧";
//	DrawRow(0, 0, 11);
//	ConsoleManager::Instance().GoToXY(69, 78);
//	cout << "▨";
//	DrawColumn(69, 60, 18);
//	ConsoleManager::Instance().GoToXY(69, 59);
//	cout << "▧";
//
//	ConsoleManager::Instance().GoToXY(75, 59);
//	cout << "▨";
//	DrawRow(0, 0, 11);
//	DrawColumn(75, 60, 18);
//	ConsoleManager::Instance().GoToXY(75, 78);
//	cout << "▧";
//	DrawRow(0, 0, 11);
//	ConsoleManager::Instance().GoToXY(99, 78);
//	cout << "▨";
//	DrawColumn(99, 60, 18);
//	ConsoleManager::Instance().GoToXY(99, 59);
//	cout << "▧";
//
//	ConsoleManager::Instance().GoToXY(105, 59);
//	cout << "▨";
//	DrawRow(0, 0, 11);
//	DrawColumn(105, 60, 18);
//	ConsoleManager::Instance().GoToXY(105, 78);
//	cout << "▧";
//	DrawRow(0, 0, 11);
//	ConsoleManager::Instance().GoToXY(129, 78);
//	cout << "▨";
//	DrawColumn(129, 60, 18);
//	ConsoleManager::Instance().GoToXY(129, 59);
//	cout << "▧";
//}

//void DrawGameButtons()
//{
//	//플레이어 카드 영역. //-20씩 시키기.
//	ConsoleManager::Instance().GoToXY(39, 57);
//	cout << "○";
//	DrawRow(38, 60, 47);
//	DrawColumn(39, 58, 22);
//	ConsoleManager::Instance().GoToXY(134, 57);
//	cout << "○";
//	DrawColumn(135, 58, 22);
//	//
//	ConsoleManager::Instance().GoToXY(149, 55);
//	cout << "◈";
//	DrawRow(0, 0, 11);
//	DrawColumn(149, 56, 23);
//	ConsoleManager::Instance().GoToXY(149, 79);
//	cout << "◈";
//	DrawRow(0, 0, 11);
//	//
//	ConsoleManager::Instance().GoToXY(149, 63);
//	cout << "◈";
//	DrawRow(0, 0, 11);
//	//
//	ConsoleManager::Instance().GoToXY(149, 71);
//	cout << "◈";
//	DrawRow(0, 0, 11);
//	//가운데
//	ConsoleManager::Instance().GoToXY(173, 55);
//	cout << "◈";
//	DrawRow(0, 0, 12);
//	DrawColumn(173, 56, 7);
//	ConsoleManager::Instance().GoToXY(173, 63);
//	cout << "◈";
//	DrawRow(0, 0, 12);
//	DrawColumn(173, 64, 7);
//	ConsoleManager::Instance().GoToXY(173, 71);
//	cout << "◈";
//	DrawRow(0, 0, 12);
//	DrawColumn(173, 72, 7);
//	ConsoleManager::Instance().GoToXY(173, 79);
//	cout << "◈";
//	DrawRow(0, 0, 12);
//
//
//	ConsoleManager::Instance().GoToXY(158, 59);
//	cout << "[4] 다이";
//	ConsoleManager::Instance().GoToXY(158, 67);
//	cout << "[5] 삥";
//	ConsoleManager::Instance().GoToXY(158, 75);
//	cout << "[6] 따당";
//
//	ConsoleManager::Instance().GoToXY(182, 59);
//	cout << "[7] 콜";
//	ConsoleManager::Instance().GoToXY(182, 67);
//	cout << "[8] 쿼터";
//	ConsoleManager::Instance().GoToXY(182, 75);
//	cout << "[9] 하프";
//
//	//카드 조합 알려주는 부분.
//
//	ConsoleManager::Instance().GoToXY(0, 57);
//	cout << "▣";
//	DrawRow(0, 0, 15);
//	ConsoleManager::Instance().GoToXY(32, 57);
//	cout << "▣";
//	DrawColumn(32, 58, 6);
//	ConsoleManager::Instance().GoToXY(32, 64);
//	cout << "▣";
//	DrawColumn(32, 65, 6);
//	ConsoleManager::Instance().GoToXY(32, 71);
//	cout << "▣";
//	DrawColumn(32, 72, 6);
//	ConsoleManager::Instance().GoToXY(32, 78);
//	cout << "▣";
//	ConsoleManager::Instance().GoToXY(0, 78);
//	cout << "▣";
//	DrawRow(0, 0, 15);
//	ConsoleManager::Instance().GoToXY(0, 71);
//	cout << "▣";
//	DrawRow(0, 0, 15);
//	ConsoleManager::Instance().GoToXY(0, 64);
//	cout << "▣";
//	DrawRow(0, 0, 15);
//}
///(N_ADD)헤더 추가 잊지 말기!
//void PrintBettingImage(BetInfo _betInfo, int playerNo) // 0-3으로 하기. 
//{
//
//	int tempX = 0;
//	int tempY = 0;
//
//	char tempArray[9][30];
//
//	switch (playerNo)
//	{
//		case 0:
//			tempX = 143;
//			tempY = 6;
//			break;
//		case 1:
//			tempX = 143;
//			tempY = 31;
//			break;
//		case 2:
//			tempX = 44;
//			tempY = 6;
//			break;
//		case 3:
//			tempX = 44;
//			tempY = 31;
//			break;
//		default:
//			cout << "wrong parameter";
//			break;
//	}
//
//
//	if (_betInfo == BetInfo::DDIE)
//	{
//
//		switch (playerNo)
//		{
//			case 0:
//				EraseArea(CardArea::P1_1);
//				EraseArea(CardArea::P1_2);
//				break;
//			case 1:
//				tempY -= 2;
//				EraseArea(CardArea::P2_1);
//				EraseArea(CardArea::P2_2);
//				break;
//			case 2:
//				EraseArea(CardArea::P3_1);
//				EraseArea(CardArea::P3_2);
//				break;
//			case 3:
//				tempY -= 2;
//				EraseArea(CardArea::P4_1);
//				EraseArea(CardArea::P4_2);
//				break;
//			default:
//				cout << "wrong parameter";
//				break;
//		}
//		ConsoleManager::Instance().GoToXY(tempX, tempY);
//		for (int i = 0; i < 17; i++)
//		{
//			for (int j = 0; j < 40; j++)
//			{
//				if (_dieMessage[i][j] == '0')
//				{
//					ConsoleManager::Instance().SetColor(DARKRED, DARKRED);
//					cout << " ";
//				}
//				else if (_dieMessage[i][j] == '8')
//				{
//					ConsoleManager::Instance().SetColor(WHITE, WHITE);
//					cout << " ";
//				}
//				else if (_dieMessage[i][j] == '9')
//				{
//					ConsoleManager::Instance().SetColor(GRAY, GRAY);
//					cout << " ";
//				}
//			}
//			ConsoleManager::Instance().GoToXY(tempX, tempY + i);
//		}
//		ResetTextColor();
//	}
//	else
//	{
//		tempX -= 40;
//		tempY -= 4;
//		if (_betInfo == BetInfo::BBING)
//		{
//			memcpy(tempArray, _bbingMessage, 30 * 9 * sizeof(char));
//		}
//		else if (_betInfo == BetInfo::CALL)
//		{
//			memcpy(tempArray, _callMessage, 30 * 9 * sizeof(char));
//		}
//		else if (_betInfo == BetInfo::DDADANG)
//		{
//			memcpy(tempArray, _ddaDangMessage, 30 * 9 * sizeof(char));
//		}
//		else if (_betInfo == BetInfo::QUARTER)
//		{
//			memcpy(tempArray, _quarterMessage, 30 * 9 * sizeof(char));
//		}
//		else if (_betInfo == BetInfo::HALF)
//		{
//			memcpy(tempArray, _halfMessage, 30 * 9 * sizeof(char));
//		}
//		else
//		{
//			cout << "error";
//		}
//
//		for (int i = 0; i < 8; i++)
//		{
//			for (int j = 0; j < 29; j++)
//			{
//				if (tempArray[i][j] == '0')
//				{
//					ConsoleManager::Instance().SetColor(WHITE, WHITE);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '1')
//				{
//					ConsoleManager::Instance().SetColor(FADEWHITE, FADEWHITE);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '2')
//				{
//					ConsoleManager::Instance().SetColor(PURPLE, PURPLE);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '3')
//				{
//					ConsoleManager::Instance().SetColor(GRAY, GRAY);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '4')
//				{
//					ConsoleManager::Instance().SetColor(LIGHTGREEN, LIGHTGREEN);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '5')
//				{
//					ConsoleManager::Instance().SetColor(GRAY, GRAY);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '6')
//				{
//					ConsoleManager::Instance().SetColor(LIGHTBLUE, LIGHTBLUE);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '7')
//				{
//					ConsoleManager::Instance().SetColor(PINK, PINK);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '8')
//				{
//					ConsoleManager::Instance().SetColor(RED, RED);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == '9')
//				{
//					ConsoleManager::Instance().SetColor(BLACK, BLACK);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == 'a')
//				{
//					ConsoleManager::Instance().SetColor(DARKRED, DARKRED);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == 'b')
//				{
//					ConsoleManager::Instance().SetColor(DARKBLUE, DARKBLUE);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == 'c')
//				{
//					ConsoleManager::Instance().SetColor(DARKYELLOW, DARKYELLOW);
//					cout << " ";
//				}
//				else if (tempArray[i][j] == 'd')
//				{
//					ConsoleManager::Instance().SetColor(YELLOW, YELLOW);
//					cout << " ";
//				}
//				else
//				{
//					cout << "Error";
//				}
//			}
//			ConsoleManager::Instance().GoToXY(tempX, tempY + i);
//		}
//		ResetTextColor();
//	}
//}

//void EraseBettingImage(int playerNo)
//{
//	int tempX = 0;
//	int tempY = 0;
//	switch (playerNo)
//	{
//		case 0:
//			tempX = 143;
//			tempY = 6;
//			break;
//		case 1:
//			tempX = 143;
//			tempY = 31;
//			break;
//		case 2:
//			tempX = 44;
//			tempY = 6;
//			break;
//		case 3:
//			tempX = 44;
//			tempY = 31;
//			break;
//		default:
//			cout << "wrong parameter";
//			break;
//	}
//
//	EraseArea(false, tempX - 40, tempY - 5, tempX - 10, tempY + 4);
//
//}

void DrawMainBoard(Player* p_player)
{
	system("mode con:cols=200 lines=80 | title=HallowUp");

	PrintManager::Instance().DrawPlayerCardsOnBoard(1);
	PrintManager::Instance().DrawPlayerCardsOnBoard(2);
	PrintManager::Instance().DrawPlayerCardsOnBoard(3);
	PrintManager::Instance().DrawPlayerCardsOnBoard(4);

	PrintManager::Instance().DrawGameButtons();
	PrintManager::Instance().AddDecoration();
	PrintManager::Instance().PutCardFrames();

	ConsoleManager::Instance().GoToXY(25, 60);
	cout << "[1]";
	ConsoleManager::Instance().GoToXY(25, 67);
	cout << "[2]";
	ConsoleManager::Instance().GoToXY(25, 74);
	cout << "[3]";

	ConsoleManager::Instance().GoToXY(199, 79);
}