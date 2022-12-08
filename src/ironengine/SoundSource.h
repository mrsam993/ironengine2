#include "Component.h"
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace ironengine
{
	/// @brief Struct that outputs sound, inherits from component
	struct SoundSource : Component
	{
		SoundSource();
		
		/// @brief Function that is called every tick
		void onTick();
	};
}