#include "Component.h"
#include <rend/rend.h>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace ironengine
{
	/// @brief Struct that allows collision, inherits from component
	struct IrcComponent : Component
	{
	private:
		SOCKET m_socket;
		std::vector<unsigned char> m_incoming;
		std::vector<unsigned char> m_outgoing;

		bool m_authenticated;
		bool m_disconnected;

	public:
		IrcComponent();
		~IrcComponent();

		void onTick();

		void authenticate();
		bool disconnected();
	};
}