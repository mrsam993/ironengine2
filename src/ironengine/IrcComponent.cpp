#include "IrcComponent.h"
#include <stdexcept>
#include <iostream>
#include <random>
#include <chrono>

namespace ironengine
{
	IrcComponent::IrcComponent()
	{
		struct addrinfo* result = NULL;

		/* Obtain list of suitable interfaces */
		addrinfo hints = { 0 };
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		// Resolve the server address and port
		int iResult = getaddrinfo("irc.libera.chat", "6667", &hints, &result);
		
		if (iResult != 0)
		{
			WSACleanup();
			throw std::runtime_error("getaddrinfo failed with error");
		}

		/* Attempt to connect to an address until one succeeds */
		int s = INVALID_SOCKET;
		addrinfo* ptr;
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			s = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (s == INVALID_SOCKET)
			{
				WSACleanup();
				std::runtime_error("socket failed with error");
			}
			iResult = connect(s, ptr->ai_addr, (int)ptr->ai_addrlen); // how to get this
			if (iResult == SOCKET_ERROR)
			{
				closesocket(s);
				s = INVALID_SOCKET;
				continue;
			}
			break;
		}
		freeaddrinfo(result);
		if (s == INVALID_SOCKET)
		{
			WSACleanup();
			throw std::runtime_error("Unable to connect to server");
		}

		m_socket = s;

		u_long mode = 1;
		int res = ioctlsocket(m_socket, FIONBIO, &mode);
		if (res != NO_ERROR)
		{
			throw std::runtime_error("ioctlsocket failed");
		}
	}

	IrcComponent::~IrcComponent()
	{
		shutdown(m_socket, SD_BOTH);

		closesocket(m_socket);
	}

	void IrcComponent::onTick()
	{
		//std::string message = "Hello World"; //send buffer m_outgoing
		//int iResult = send(m_socket, message.c_str(), (int)message.length(), 0); //iresult = bytes
		//if (iResult == 0)
		//{
		//	// Connection closed. Close.
		//	m_disconnected = true;
		//	return;
		//}
		//else if (iResult == SOCKET_ERROR)
		//{
		//	// Connection error. Close.
		//	m_disconnected = true;
		//	return;
		//}

		//remove bytes from outgoing vector.erase(begin, begin+iResult);

		char buffer[128] = { 0 };
		int iResult = recv(m_socket, buffer, sizeof(buffer), 0);
		if (iResult == 0)
		{
			//
			m_disconnected = true;
			return;	
		}
		else if (iResult == SOCKET_ERROR)
		{
			//
			int wsaError = WSAGetLastError();
			if (wsaError != WSAEWOULDBLOCK)
			{
				m_disconnected = true;
			}
			return;
		}

		std::cout << buffer;

		//fill incoming with bytes
		//read and handle, then clear
	}

	void IrcComponent::authenticate()
	{
		//fill outgoing buffer
		//m_outgoing
		 
		
		//srand(time(NULL));
		//std::cout << rand() % (999 - 100);
		//NICK ie111
		//USER ie111 * * :ie111 ie111
		//JOIN ironEngineGameEngineProgramming22/23
	}

	bool IrcComponent::disconnected()
	{
		return m_disconnected;
	}
}