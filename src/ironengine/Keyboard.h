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
		// Change the key ID appropriately depending on the state of the key
		KeyState(bool _down, uint64_t _updateID) : down(_down)
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

		// Reset the state of the key
		bool down = false;
		uint64_t pressed = 0;
		uint64_t released = 0;
	};

	/// @brief Keyboard and mouse input
	class Keyboard
	{
		// Friend declarations
		friend struct Core;

	private:
		/// @brief All the keys we want to keep track of
		std::vector<int> m_keys;

		/// @brief All the keys that are currently held down
		std::vector<int> m_keysDown;

		/// @brief All the keys that are currently not held down
		std::vector<int> m_keysUp;

		/// @brief Allows the keyboard to be updated on call
		void Update();
	
	public:
		/// @brief Basic constructor for the keyboard
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