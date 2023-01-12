#include "Component.h"
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace ironengine
{
	struct Audio;

	/// @brief Struct that listens for sound, inherits from component
	struct SoundListener : Component
	{
	private:
		/// @brief Function that updates every tick allowing constant updates
		void onTick();

	public:
		/// @brief Initial setup for the listener, only called once 
		void onInit();
	};
}