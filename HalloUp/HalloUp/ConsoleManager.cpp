#include "ConsoleManager.h"
#include "GameManager.h"
#include <Windows.h>
#include <iostream>

ConsoleManager& ConsoleManager::Instance()
{
	static ConsoleManager* CM = new ConsoleManager();
	return *CM;
}
void ConsoleManager::ChangeConsloePosition(int x, int y)
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
void ConsoleManager::GoToXY(int x, int y)
{
	COORD Pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void ConsoleManager::SetColor(unsigned short text, unsigned short background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}
void ConsoleManager::CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ä¿¼­ ±½±â (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ä¿¼­ Visible TRUE(º¸ÀÓ) FALSE(¼û±è)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void ConsoleManager::ChangeConsoleSize(int x, int y)
{
	char g_command[COMMAND_SIZE] = { '\0' };
	// cols°¡ °¡·Î lines°¡ ¼¼·Î
	sprintf(g_command, "mode con:cols=%d lines=%d | title Hallo Up", x, y);
	system(g_command);
}
void ConsoleManager::ChangeFont()
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 12;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}