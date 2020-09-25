#include "TCPSocket.h"



TCPSocket::TCPSocket()
{
}


TCPSocket::~TCPSocket()
{
}

bool TCPSocket::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{

		std::cout << "Error initialising SDL." << std::endl;
		system("pause");
		return 0;
	}

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
	//it means myself: 127.0.0.1
	//if (SDLNet_ResolveHost(&m_IP, IP.getString(), port) == -1)
	if (SDLNet_ResolveHost(&m_IP, "127.0.0.1", 1234) == -1)
	{
		std::cout << "Error resolving host." << std::endl;
		system("pause");
		return 0;

	}
	std::cout << "User Connected" << std::endl;
	m_socket = SDLNet_TCP_Open(&m_IP);
	isClientOn = true;
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
