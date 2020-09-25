#include "TCPSocket.h"



TCPSocket::TCPSocket()
{
}


TCPSocket::~TCPSocket()
{
}

bool TCPSocket::Initialize()
{
	if (SDLNet_Init() == -1)
	{

		std::cout << "Error initialising SDL networking sub-system." << std::endl;
		system("pause");
		return 0;
	}
	return 1;
}

bool TCPSocket::Open()
{
	if (SDLNet_ResolveHost(&m_IP, nullptr, 1234) == -1)
	{
		std::cout << "Error creating server." << std::endl;
		system("pause");
		return 0;

	}

	return 1;
}

void TCPSocket::Close()
{
	SDLNet_TCP_Close(m_socket);
}

void TCPSocket::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}
