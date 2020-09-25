#include "TCPServer.h"



TCPServer::TCPServer()
{
}


TCPServer::~TCPServer()
{
	nullptr;
}

bool TCPServer::Listen()
{
	

	m_clientSockets[key] = nullptr;
	m_socket = SDLNet_TCP_Open(&m_IP);
	
	while (m_clientSockets[key] == nullptr)
	{
		if (m_socket != nullptr)
		{
			m_clientSockets[key] = SDLNet_TCP_Accept(m_socket);
			std::cout << "... " << std::endl;
			SDL_Delay(1500);
		}
	}
	m_socket = nullptr;

	std::cout << "Welcome User n: " << key << std::endl;
	key++;
	isClientOn = true;
	return true;
}

//bool TCPServer::Listen(const String& clientID)
//{
//	TCPsocket tempSocket = nullptr;
//	tempSocket = SDLNet_TCP_Accept(m_socket);
//	if (!tempSocket)
//	{
//		std::cout << "Cannot connet with client" << std::endl;
//		SDL_Delay(500);
//		return false;
//	}
//
//	m_clientSockets[clientID] = tempSocket;
//
//	return true;
//}

bool TCPServer::SendMessage(const String& message)
{
	int lenght = message.Length() + 1;
	for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
	{
		if (it->second != nullptr)
		{
			if (SDLNet_TCP_Send(it->second, message.getString(), lenght) < lenght)
			{
				std::cout << "Error sending the message." << std::endl;
				system("pause");
				return 0;
			}
		}

	}

	return 1;
}

bool TCPServer::ReceiveMessage(String& message)
{
	char response[2000];



	for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
	{
		if (it->second != nullptr)
		{
			if (response != "")
			{

				if (SDLNet_TCP_Recv(it->second, response, 2000) <= 0)
				{
					std::cout << "Error receiving the message." << std::endl;
					system("pause");
					return 0;
				}
			}
			if (response != "")
			{
				system("color e2");
				SetConsoleTextAttribute(hConsole, 1);
				std::cout << response << std::endl;
				m_response = response;
				system("color e4");
			}
		}


	}
	
	return 1;

}

void TCPServer::Close()
{
	SDLNet_TCP_Close(m_socket);
	for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); it++)
	{
		SDLNet_TCP_Close(it->second);
	}
}
