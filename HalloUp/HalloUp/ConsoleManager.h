#pragma once
class ConsoleManager
{
private:
	ConsoleManager() {}
	ConsoleManager(const ConsoleManager& ref) {}
	~ConsoleManager() {}
public:
	static ConsoleManager& Instance();

	// �ܼ�â ��ġ �ٲٴ� �Լ�
	void ChangeConsloePosition(int x, int y);		// ConsoleManager

	// �ֿܼ��� Ŀ�� ��ġ �ٲٴ� �Լ�
	void GoToXY(int x, int y);		// ConsoleManager

	// ���� �� �ٲٴ� �Լ�
	void SetColor(unsigned short text, unsigned short background);		// Consolemanager

	// �ֿܼ��� Ŀ�� �Ⱥ��̰� �ϴ� �Լ�
	void CursorView();		// ConsoleManager

	// �ܼ�â ũ�� �ٲٴ� �Լ�
	void ChangeConsoleSize(int x, int y);		// ConsoleManager

	// �۾� ũ�� �ٲٴ� �Լ�
	void ChangeFont();		// ConsoleManger
};