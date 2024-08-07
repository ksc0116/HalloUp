#pragma once
class InputManager
{
private:
	InputManager() {}
	InputManager(const InputManager& ref) {}
	~InputManager() {}
public:
	static InputManager& Instance();

	// ���� ī�� �� �� ������ �� �Է��ϴ� �Լ� (������ �������� ����)
	void OpenCardInput();	// InputManager

	// 1 2�� �Է� ������ Ű���� �Է� �Լ�
	int KeyBoardControlOneTwo();	// InputManager

	// 1 2 3�� �Է� ������ Ű���� �Է� �Լ�
	int KeyBoardControlOneTwoThree();	// Inputmanager

	// 4 5 6 7 8 9�� �Է� ������ �Լ�
	int KeyBoardControlBettingSystem();	//  InputManager

	// ���� �Է�
	bool BettingInput(bool isFirst);	// InputManager

	// Ű���� �Է� ó�� �Լ� (��, ��, ��, ��, ����)
	int KeyBoardControl();		//InputManager
};

