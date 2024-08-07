#include "TcpClient.h"
#include "GameManager.h"

std::mutex _mutex;

void TcpClient::MakePacket()
{
	if (!CheckPacketRecv())
		return;

	volatile char byteStream[BUFFERSIZE];

	switch ((S2Ctype)ReadPacketByte(byteStream))
	{
	case S2Ctype::EchoTestOne:	// 테스트용
	{
		S2C::EchoTestOne* echoTestOne = (S2C::EchoTestOne*)byteStream;
		
		std::cout << "Test One Int 수신 : " << echoTestOne->testint << std::endl;
		
		break;
	}
	case S2Ctype::EchoTestAll:	// 테스트용
	{
		S2C::EchoTestAll* echoTestAll = (S2C::EchoTestAll*)byteStream;

		std::cout << "Test All Int 수신 : " << echoTestAll->testint << std::endl;
		
		break;
	}
	case S2Ctype::AcceptInfo:	// 서버에 접속하자마자 ID index candy 받음 설정해줘야함
	{
		S2C::AcceptInfo* acceptInfo = (S2C::AcceptInfo*)byteStream;
		
		// 접속한 플레이어 초기화
		player.id = acceptInfo->id;
		player.index = acceptInfo->index;
		player.candy = acceptInfo->candy;
		player.isLogIn = true;

		players[player.index].id = player.id;
		players[player.index].index = player.index;
		players[player.index].candy = player.candy;
		players[player.index].isLogIn = true;

		//std::cout << "My index : " << acceptInfo->index << std::endl;
		
		break;
	}
	case S2Ctype::CurrentConnectedUserInfo:	// 접속하면 이미 접속되어있는 유저들 정보 받음
	{
		S2C::CurrentConnectedUserInfo* currentConnectedUserInfo = (S2C::CurrentConnectedUserInfo*)byteStream;
		int index = currentConnectedUserInfo->index;
		
		players[index].id = currentConnectedUserInfo->id;
		players[index].index = currentConnectedUserInfo->index;
		players[index].candy = currentConnectedUserInfo->candy;
		// 새로 접속한 사람은 이미 접속한 사람의 캔디를 출력
		++curPlayerCount;
		GameManager::Instance().CurrentLogInPlayerCandyPrint();

		// 입장할 때 내가 몇번인지 출력함
		ConsoleManager::Instance().GoToXY(2, 55);
		std::cout << "My Player : " << "player"<<player.index + 1;

		break;
	}
	case S2Ctype::EnterUserInfo:	// 이미 접속해 있을 때 서버에 접속한 유저의 정보 받음
	{
		S2C::EnterUserInfo* enterUserInfo = (S2C::EnterUserInfo*)byteStream;
		
		int index = enterUserInfo->index;
		players[index].id = enterUserInfo->id;
		players[index].index = enterUserInfo->index;
		players[index].candy = enterUserInfo->candy;
		players[index].isGameOver = false;
		players[index].isDie = false;
		players[index].isCall = false;
		players[index].isCircuit = false;
		players[index].isLogIn = false;
		players[index].isPreference = false;
		
		// 이미 있던 사람은 새로 들어온 사람의 캔디를 출력
		++curPlayerCount;
		GameManager::Instance().CurrentLogInPlayerCandyPrint();

		break;
	}
	case S2Ctype::RandomSeed:	// 게임 시작 시 랜덤 시드 부여 이걸로 랜덤함수 돌림
	{
		S2C::RandomSeed* randomSeed = (S2C::RandomSeed*)byteStream;
		
		GameManager::Instance().MixCard(randomSeed->randomSeed);

		break;
	}
	case S2Ctype::StartingGame:	// 게임 시작 알리는 패킷 이거 받으면 게임시작
	{
		S2C::StartingGame* startingGame = (S2C::StartingGame*)byteStream;
		preferencePlayerIndex = startingGame->index;
		// isAllPlayerLogIn를 true로 바꿈
		// 모두가 모였을 때 게임시작 버튼 누르면 게임이 시작되는 함수 추가 해야함
		GameManager::Instance().AllPlayerLogIn();
		PlayNextGame();

		break;
	}
	case S2Ctype::ReturnOpeningCard:	
	{	// 남들이 오픈한 카드 정보, 다 오픈하면 한번에 보낼지 클라에서 모두 오픈하면 보여주는걸로 처리할지는 고민중

		S2C::ReturnOpeningCard* returnOpeningCard = (S2C::ReturnOpeningCard*)byteStream;

		GameManager::Instance().GetOpenCardInfo(returnOpeningCard->index, returnOpeningCard->cardIndex);

		break;
	}
	case S2Ctype::ReturnFirstBet:	//첫번째 베팅때 사용
	{	
		S2C::ReturnFirstBet* returnFirstBet = (S2C::ReturnFirstBet*)byteStream;

		int index = returnFirstBet->index;
		int betIndex = returnFirstBet->betIndex;
		// 화살표 지우는 함수
		PrintManager::Instance().DleteArrow();

		//베팅을 시작해주세요. 지우기9
		PrintManager::Instance().EraseArea(true, 75, 50, 95, 50);

		++betCount;
		
		// players배열 최신화 // totalGameCandy와 frontPlayerBettingCandy 최신화
		GameManager::Instance().UpdatePlayerBettingInfo(index, betIndex);

		// 최고 베팅 금액 정하기
		if (players[preferencePlayerIndex].isDie && maxBettingCandy == 0)
		{
			isPreferencePlayerDie = true;
		}
		else
		{
			if (maxBettingCandy < players[index].myBettingCandy)
			{
				maxBettingCandy = players[index].myBettingCandy;
			}
		}
		if (betIndex == 4)
		{
			PrintManager::Instance().PrintDie(index);
		}
		// 각 화면에 어떤 플레이어가 무엇을 베팅했는지 보여줌
		PrintManager::Instance().PrintBettingInfo(index, betIndex);
		// 각 화면에 다른 플레이어의 캔디 현황을 보여줌
		PrintManager::Instance().PrintPlayerCandy(index);
		// 각 화면에 게임 총 캔디를 보여줌
		PrintManager::Instance().PrintTotalGameCandy();
		// 화면에 모든 베팅 버튼 출력
		PrintManager::Instance().PrintAllBettingButton();
		if (betIndex == 4)
		{
			++diePlayerCount;
		}
		else if (betIndex == 7)
		{
			++callPlayerCount;
		}
		else
		{
			callPlayerCount = 0;
		}

		anotherBetWait = false;
		break;
	}
	case S2Ctype::ReturnSecondBet:	//두번째 베팅때 사용
	{	
		S2C::ReturnSecondBet* returnFirstBet = (S2C::ReturnSecondBet*)byteStream;


		break;
	}
	case S2Ctype::ReturnSelectCombination:	//카드 조합 두개 넘어옴
	{
		S2C::ReturnSelectCombination * packet = (S2C::ReturnSelectCombination*)byteStream;

		// 패킷으로 넘어온 정보를 players배열에 초기화
		GameManager::Instance().UpdateMatchCardSelect(packet->cardIndex1, packet->cardIndex2,packet->index);

		break;
	}
	case S2Ctype::ExitUserInfo:
	{
		auto* packet = (S2C::ExitUserInfo*)byteStream;

		int id = packet->id;
		int index = packet->index;

		players[index].id = -1;
		players[index].candy = 0;
		players[index].myJokbo = YET;
		if (!players[index].isGameOver)
		{
			if(!players[index].isDie )
			{
				players[index].isGameOver = true;
				players[index].isDie = true;
				++diePlayerCount;
			}
		}
		if ((betCount % 4) == index)
		{
			++betCount;
			anotherBetWait = false;
		}

		--curPlayerCount;

		// 각 화면에 다른 플레이어의 캔디 현황을 보여줌
		PrintManager::Instance().PrintPlayerCandy(index);

		break;
	}
	default:
		break;
	}

	MakePacket();
}

TcpClient::TcpClient()
	:_maxBufferSize(BUFFERSIZE), _size(0)
{
	_recvBufferQueue = new char[_maxBufferSize];

}

TcpClient::~TcpClient()
{
	std::cout << "접속종료" << std::endl;
	delete[] _recvBufferQueue;
	closesocket(sock);
	WSACleanup();
}

void TcpClient::TCPClientInit()
{
	if (WSAStartup(MAKEWORD(2, 2), &_wsa) != 0)
	{
		std::cout << "WSAStartup Fail." << std::endl;
		return;
	}

	sock = socket(AF_INET,
		SOCK_STREAM, 0);

	ZeroMemory(&_sa, sizeof(_sa));
	_sa.sin_family = AF_INET;
	_sa.sin_port = htons(PORT);
	_sa.sin_addr.s_addr = inet_addr(IP);

	int iRet = connect(sock, (sockaddr*)&_sa, sizeof(_sa));
	if (iRet == SOCKET_ERROR)
	{
		std::cout << "Connect Fail." << std::endl;
		return;
	}

	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);

	//std::cout << "Server Connet!" << std::endl;
}

void TcpClient::TCPClientRecv()
{
	while (true)
	{
		char szRecvBuffer[BUFFERSIZE] = { 0, };
		int iRecvByte = recv(sock, szRecvBuffer, BUFFERSIZE, 0);
		
		if (iRecvByte == 0)
		{
			std::cout << "서버종료됨.." << std::endl;
			break;
		}

		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout << "비정상 서버종료됨.." << std::endl;
				break;
			}
			continue;
		}

		PushBuffer(szRecvBuffer, iRecvByte);
	}
}

void TcpClient::TCPClientStart()
{
	TCPClientInit();
	
	std::thread tcpClientRecv([this] {this->TCPClientRecv(); });
	//std::thread testFunc([this] {this->TestFunc(); });
	
	tcpClientRecv.detach();

}

void TcpClient::ReSizeBuffer()
{
	char* temp = new char[_maxBufferSize <<= 1];
	memset(temp, 0, sizeof(_maxBufferSize));
	memcpy(temp, (char*)_recvBufferQueue, _size);
	delete[] _recvBufferQueue;
	_recvBufferQueue = temp;
}

void TcpClient::PushBuffer(char* buf, int size)
{
	_mutex.lock();

	if (_size + size > _maxBufferSize)
		ReSizeBuffer();

	memcpy((char*)_recvBufferQueue + _size, buf, size);

	_size += size;

	//std::cout << "Recv : " << _size << std::endl;
	//std::cout << "Queue size : " << _size << std::endl;
	_mutex.unlock();

	MakePacket();
}

bool TcpClient::CheckPacketRecv()
{
	if (_size < 1)
		return false;

	if (_size < (int)_recvBufferQueue[0])
		return false;

	return true;
}

char TcpClient::ReadPacketByte(volatile char* buf)
{
	_mutex.lock();

	int size = (int)_recvBufferQueue[0];
	char type = _recvBufferQueue[1];

	memcpy((void*)buf, (char*)_recvBufferQueue, size);

	_size -= size;

	memmove((char*)_recvBufferQueue, (char*)_recvBufferQueue + size, _size);

	memset((char*)_recvBufferQueue + _size, 0, size);

	_mutex.unlock();

	return type;
}


void TcpClient::SendToServer(void* packet)
{
	char* buf = (char*)packet;
	int iSendByte = send(sock, buf, (int)buf[0], 0);

	if (iSendByte == SOCKET_ERROR)
	{
		int iError = WSAGetLastError();
		if (iError != WSAEWOULDBLOCK)
		{
			std::cout << "서버 비정상 접속종료됨." << std::endl;
			TcpClient::~TcpClient();
		}
		return;
	}

	//std::cout << "Server에 " << sock << " : " << iSendByte << " 보냄." << std::endl;
}
