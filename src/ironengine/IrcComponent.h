#ifndef __EMSCRIPTEN__

#include "Component.h"
#include <rend/rend.h>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace ironengine
{
	/// @brief Struct that allows connection to online services, inherits from component
	struct IrcComponent : Component
	{
	private:
		/// @brief Socket that is assigned after the initial connection
		SOCKET m_socket;
		/// @brief Buffer of data that is coming from the irc
		std::vector<unsigned char> m_incoming;
		/// @brief Buffer of data that is going into the irc
		std::vector<unsigned char> m_outgoing;

		/// @brief Manages authentication and successful logins
		bool m_authenticated;
		/// @brief Manages disconections from the irc
		bool m_disconnected;

	public:
		/// @brief Basic constructor for the irc component
		IrcComponent();
		/// @brief Basic destructor for the irc component
		~IrcComponent();

		/// @brief Function that updates every tick allowing constant updates
		void onTick();

		/// @brief Logging the user into the irc service
		void authenticate();
		/// @brief Properly disconnecting the user from the irc service
		bool disconnected();
	};
}

#endif