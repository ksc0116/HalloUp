#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <mutex>
#include <thread>
#include "GameManager.h"

#include "PacketC2S.h"
#include "PacketS2C.h"
#pragma comment	(lib, "ws2_32.lib")

//#include "PacketC2S.h"
//#include "PacketS2C.h"

#define BUFFERSIZE 256
#define IP "127.0.0.1"
#define PORT 22000

class TcpClient
{
private:
	WSADATA _wsa;
	SOCKADDR_IN _sa;

	volatile char* _recvBufferQueue;
	unsigned int _maxBufferSize;
	int _size;

	void ReSizeBuffer();

	void TCPClientInit();
	void TCPClientRecv();
	void PushBuffer(char* buf, int size);
	bool CheckPacketRecv();
	char ReadPacketByte(volatile char* buf);
	void MakePacket();
public:
	TcpClient();
	~TcpClient();

	SOCKET sock;

	void TCPClientStart();

	void SendToServer(void*);

};
