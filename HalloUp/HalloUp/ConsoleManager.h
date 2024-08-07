#pragma once
class ConsoleManager
{
private:
	ConsoleManager() {}
	ConsoleManager(const ConsoleManager& ref) {}
	~ConsoleManager() {}
public:
	static ConsoleManager& Instance();

	// 콘솔창 위치 바꾸는 함수
	void ChangeConsloePosition(int x, int y);		// ConsoleManager

	// 콘솔에서 커서 위치 바꾸는 함수
	void GoToXY(int x, int y);		// ConsoleManager

	// 글자 색 바꾸는 함수
	void SetColor(unsigned short text, unsigned short background);		// Consolemanager

	// 콘솔에서 커서 안보이게 하는 함수
	void CursorView();		// ConsoleManager

	// 콘솔창 크기 바꾸는 함수
	void ChangeConsoleSize(int x, int y);		// ConsoleManager

	// 글씨 크기 바꾸는 함수
	void ChangeFont();		// ConsoleManger
};