#pragma once
#include <map>
#include<Windows.h>
#include "TCPSocket.h"
class TCPServer :
	public TCPSocket
{
public:
	TCPServer();
	~TCPServer();

public:
	bool Listen();
	/*bool Listen(const String& clientID);*/
	bool SendMessage(const String& message);
	bool ReceiveMessage(String& message);
	void Close();

public:
	bool GetClientOn() { return isClientOn; }
	String GetResponse() { return m_response; }

private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	TCPsocket m_clientSocket;
	std::map<int, TCPsocket> m_clientSockets;
	//std::map<String, TCPsocket> m_clientSockets;
	//std::map<String, TCPsocket>::key_compare mycomp = m_clientSockets.key_comp();
	int key = 0;
	bool isClientOn = false;
	String m_response;
		
};

