#pragma once
class InputManager
{
private:
	InputManager() {}
	InputManager(const InputManager& ref) {}
	~InputManager() {}
public:
	static InputManager& Instance();

	// 나의 카드 중 뭘 오픈할 지 입력하는 함수 (서버에 정보까지 보냄)
	void OpenCardInput();	// InputManager

	// 1 2만 입력 가능한 키보드 입력 함수
	int KeyBoardControlOneTwo();	// InputManager

	// 1 2 3만 입력 가능한 키보드 입력 함수
	int KeyBoardControlOneTwoThree();	// Inputmanager

	// 4 5 6 7 8 9만 입력 가능한 함수
	int KeyBoardControlBettingSystem();	//  InputManager

	// 베팅 입력
	bool BettingInput(bool isFirst);	// InputManager

	// 키도브 입력 처리 함수 (상, 하, 좌, 우, 선택)
	int KeyBoardControl();		//InputManager
};

