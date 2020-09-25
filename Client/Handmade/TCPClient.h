#pragma once
#include "TCPSocket.h"
#include<Windows.h>
class TCPClient :
	public TCPSocket
{
public:
	TCPClient();
	~TCPClient();
public:
	

	bool SendMessage(const String& message);
	bool ReceiveMessage(String& message);

	String GetResponse() { return m_response; }

private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	String m_response;
};

