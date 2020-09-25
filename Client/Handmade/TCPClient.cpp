#include "TCPClient.h"



TCPClient::TCPClient()
{
}


TCPClient::~TCPClient()
{
}

bool TCPClient::SendMessage(const String& message)
{
	int lenght = message.Length() + 1;
	if (SDLNet_TCP_Send(m_socket, message.getString(), lenght) < lenght)
	{
		std::cout << "Error sending the message." << std::endl;
		system("pause");
		return 0;
	}
	return 1;
}

bool TCPClient::ReceiveMessage(String& message)
{
	char response[2000];
	if (SDLNet_TCP_Recv(m_socket, response, 2000) <= 0)
	{
		std::cout << "Error receiving the message." << std::endl;
		system("pause");
		return 0;
	}
	system("color e2");
	m_response = response;
	//std::cout << response << std::endl;
	system("color e4");
	return 1;
}
