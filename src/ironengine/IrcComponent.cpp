#ifndef __EMSCRIPTEN__

#include "IrcComponent.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <random>
#include <chrono>

namespace ironengine
{
	IrcComponent::IrcComponent()
	{
		// Declare local variables
		struct addrinfo* result = NULL;
		addrinfo hints = { 0 };
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		int iResult = getaddrinfo("irc.libera.chat", "6667", &hints, &result);
		
		// Check initial connection to the irc
		if (iResult != 0)
		{
			WSACleanup();
			throw std::runtime_error("getaddrinfo failed with error");
		}

		// Attempt to connect to an address until one succeeds
		int s = INVALID_SOCKET;
		addrinfo* ptr;
		// Loop though all possible address
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			// Check if the socket is valid
			s = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (s == INVALID_SOCKET)
			{
				WSACleanup();
				std::runtime_error("socket failed with error");
			}
			// Check for socket errors after attempted connection
			iResult = connect(s, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(s);
				s = INVALID_SOCKET;
				continue;
			}
			break;
		}
		freeaddrinfo(result);
		// Ensure the socket is valid
		if (s == INVALID_SOCKET)
		{
			WSACleanup();
			throw std::runtime_error("Unable to connect to server");
		}

		// Check for errors with the input and output of the socket
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
		// Shutdown and close the socket
		shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
	}

	void IrcComponent::onTick()
	{
		// Create a buffer and fill it with data from the irc
		char buffer[4096] = { 0 };
		int iResult = recv(m_socket, buffer, sizeof(buffer), 0);
		// Check if there is still a connection
		if (iResult == 0)
		{
			m_disconnected = true;
			return;	
		}
		// Check if there is a socket error
		else if (iResult == SOCKET_ERROR)
		{
			int wsaError = WSAGetLastError();
			if (wsaError != WSAEWOULDBLOCK)
			{
				m_disconnected = true;
			}
			return;
		}

		// Convert the irc data to a string
		std::string sBuffer = std::string(buffer);
		//std::cout << sBuffer << std::endl;

		// Ensure that login data is sent at the right time
		if (sBuffer.find("No Ident response") != std::string::npos) {
			authenticate();
		}

		if (sBuffer.find(":+iw") != std::string::npos) {
			std::string message = "join #IRONENGINE5220251\n";
			int iResult = send(m_socket, message.c_str(), (int)message.length(), 0);
		}

		if (sBuffer.find("#IRONENGINE5220251 :End of /NAMES list.") != std::string::npos) {
			std::string message = "PRIVMSG #IRONENGINE5220251 : TEST\n";
			int iResult = send(m_socket, message.c_str(), (int)message.length(), 0);
		}
	}

	void IrcComponent::authenticate()
	{
		// Assign a random user number for the program
		srand(time(NULL));
		int id = rand() % (9999 - 1000);
		std::string sId = std::to_string(id);
		
		// Send the login details to the irc 
		std::string message = "nick S5220251GEP";
		message.append(sId);
		message.append("\nuser S5220251GEP");
		message.append(sId);
		message.append(" * * :Anon Anon\n");

		int iResult = send(m_socket, message.c_str(), (int)message.length(), 0);
		// Check if the connection is closed
		if (iResult == 0)
		{
			m_disconnected = true;
			return;
		}
		// Check for connection errors
		else if (iResult == SOCKET_ERROR)
		{
			m_disconnected = true;
			return;
		}
	}

	bool IrcComponent::disconnected()
	{
		// Check if a disconnect has occured
		return m_disconnected;
	}
}

#endif