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
	case S2Ctype::EchoTestOne:	// �׽�Ʈ��
	{
		S2C::EchoTestOne* echoTestOne = (S2C::EchoTestOne*)byteStream;
		
		std::cout << "Test One Int ���� : " << echoTestOne->testint << std::endl;
		
		break;
	}
	case S2Ctype::EchoTestAll:	// �׽�Ʈ��
	{
		S2C::EchoTestAll* echoTestAll = (S2C::EchoTestAll*)byteStream;

		std::cout << "Test All Int ���� : " << echoTestAll->testint << std::endl;
		
		break;
	}
	case S2Ctype::AcceptInfo:	// ������ �������ڸ��� ID index candy ���� �����������
	{
		S2C::AcceptInfo* acceptInfo = (S2C::AcceptInfo*)byteStream;
		
		// ������ �÷��̾� �ʱ�ȭ
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
	case S2Ctype::CurrentConnectedUserInfo:	// �����ϸ� �̹� ���ӵǾ��ִ� ������ ���� ����
	{
		S2C::CurrentConnectedUserInfo* currentConnectedUserInfo = (S2C::CurrentConnectedUserInfo*)byteStream;
		int index = currentConnectedUserInfo->index;
		
		players[index].id = currentConnectedUserInfo->id;
		players[index].index = currentConnectedUserInfo->index;
		players[index].candy = currentConnectedUserInfo->candy;
		// ���� ������ ����� �̹� ������ ����� ĵ�� ���
		++curPlayerCount;
		GameManager::Instance().CurrentLogInPlayerCandyPrint();

		// ������ �� ���� ������� �����
		ConsoleManager::Instance().GoToXY(2, 55);
		std::cout << "My Player : " << "player"<<player.index + 1;

		break;
	}
	case S2Ctype::EnterUserInfo:	// �̹� ������ ���� �� ������ ������ ������ ���� ����
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
		
		// �̹� �ִ� ����� ���� ���� ����� ĵ�� ���
		++curPlayerCount;
		GameManager::Instance().CurrentLogInPlayerCandyPrint();

		break;
	}
	case S2Ctype::RandomSeed:	// ���� ���� �� ���� �õ� �ο� �̰ɷ� �����Լ� ����
	{
		S2C::RandomSeed* randomSeed = (S2C::RandomSeed*)byteStream;
		
		GameManager::Instance().MixCard(randomSeed->randomSeed);

		break;
	}
	case S2Ctype::StartingGame:	// ���� ���� �˸��� ��Ŷ �̰� ������ ���ӽ���
	{
		S2C::StartingGame* startingGame = (S2C::StartingGame*)byteStream;
		preferencePlayerIndex = startingGame->index;
		// isAllPlayerLogIn�� true�� �ٲ�
		// ��ΰ� ���� �� ���ӽ��� ��ư ������ ������ ���۵Ǵ� �Լ� �߰� �ؾ���
		GameManager::Instance().AllPlayerLogIn();
		PlayNextGame();

		break;
	}
	case S2Ctype::ReturnOpeningCard:	
	{	// ������ ������ ī�� ����, �� �����ϸ� �ѹ��� ������ Ŭ�󿡼� ��� �����ϸ� �����ִ°ɷ� ó�������� �����

		S2C::ReturnOpeningCard* returnOpeningCard = (S2C::ReturnOpeningCard*)byteStream;

		GameManager::Instance().GetOpenCardInfo(returnOpeningCard->index, returnOpeningCard->cardIndex);

		break;
	}
	case S2Ctype::ReturnFirstBet:	//ù��° ���ö� ���
	{	
		S2C::ReturnFirstBet* returnFirstBet = (S2C::ReturnFirstBet*)byteStream;

		int index = returnFirstBet->index;
		int betIndex = returnFirstBet->betIndex;
		// ȭ��ǥ ����� �Լ�
		PrintManager::Instance().DleteArrow();

		//������ �������ּ���. �����9
		PrintManager::Instance().EraseArea(true, 75, 50, 95, 50);

		++betCount;
		
		// players�迭 �ֽ�ȭ // totalGameCandy�� frontPlayerBettingCandy �ֽ�ȭ
		GameManager::Instance().UpdatePlayerBettingInfo(index, betIndex);

		// �ְ� ���� �ݾ� ���ϱ�
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
		// �� ȭ�鿡 � �÷��̾ ������ �����ߴ��� ������
		PrintManager::Instance().PrintBettingInfo(index, betIndex);
		// �� ȭ�鿡 �ٸ� �÷��̾��� ĵ�� ��Ȳ�� ������
		PrintManager::Instance().PrintPlayerCandy(index);
		// �� ȭ�鿡 ���� �� ĵ�� ������
		PrintManager::Instance().PrintTotalGameCandy();
		// ȭ�鿡 ��� ���� ��ư ���
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
	case S2Ctype::ReturnSecondBet:	//�ι�° ���ö� ���
	{	
		S2C::ReturnSecondBet* returnFirstBet = (S2C::ReturnSecondBet*)byteStream;


		break;
	}
	case S2Ctype::ReturnSelectCombination:	//ī�� ���� �ΰ� �Ѿ��
	{
		S2C::ReturnSelectCombination * packet = (S2C::ReturnSelectCombination*)byteStream;

		// ��Ŷ���� �Ѿ�� ������ players�迭�� �ʱ�ȭ
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

		// �� ȭ�鿡 �ٸ� �÷��̾��� ĵ�� ��Ȳ�� ������
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
	std::cout << "��������" << std::endl;
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
			std::cout << "���������.." << std::endl;
			break;
		}

		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				std::cout << "������ ���������.." << std::endl;
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
			std::cout << "���� ������ ���������." << std::endl;
			TcpClient::~TcpClient();
		}
		return;
	}

	//std::cout << "Server�� " << sock << " : " << iSendByte << " ����." << std::endl;
}
