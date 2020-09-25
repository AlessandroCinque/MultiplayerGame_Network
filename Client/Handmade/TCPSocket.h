#pragma once
#include <iostream>
#include<Windows.h>
#include "String.h"

#include <SDL.h>
#include <SDL_net.h>
class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

public:
	bool Initialise();
	bool Open();
	void Close();
	void ShutDown();

	bool GetClientOn() { return isClientOn; }

protected:
	IPaddress m_IP;
	TCPsocket m_socket;

	bool isClientOn = false;
};

