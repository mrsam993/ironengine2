#include <vector>
#include <SDL2/SDL_keycode.h>

namespace ironengine
{
	/// @brief Enum to encapsulate keycodes
	struct KeyCode
	{
		// Arrow keys
		static const int up = SDLK_UP;
		static const int right = SDLK_RIGHT;
		static const int down = SDLK_DOWN;
		static const int left = SDLK_LEFT;
	};

	/// @brief Information about the state of the key
	struct KeyState
	{
		KeyState(bool _down, uint64_t _updateID) :
			down(_down)
		{
			if (_down)
			{
				pressed = _updateID;
			}
			else
			{
				released = _updateID;
			}
		}

		bool down = false;
		uint64_t pressed = 0;
		uint64_t released = 0;
	};

	/// @brief Keyboard and mouse input
	class Keyboard
	{
		friend struct Core;

	private:
		/// @brief TEST
		bool m_quit;
		/// @brief TEST
		uint64_t m_updateCount;

		/// @brief TEST
		std::vector<int> m_keys;

		/// @brief TEST
		std::vector<int> m_keysDown;

		/// @brief TEST
		std::vector<int> m_keysUp;

		/// @brief TEST
		void Update();
	
	public:
		/// @brief TEST
		Keyboard();

		/// @brief Find out if a key is being pressed
		/// @param _key The key in question
		/// @return If the key is currently being pressed
		bool GetKey(int _key) const;

		/// @brief Find out if a key is being pressed down
		/// @param _key The key in question
		/// @return If the key is currently being pressed down
		bool GetKeyDown(int _key) const;

		/// @brief Find out if a key is being released
		/// @param _key The key in question
		/// @return If the key is currently being released
		bool GetKeyUp(int _key) const;
	};
}