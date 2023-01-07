#include "Component.h"
#include <rend/rend.h>
#include <AL/al.h>
#include <AL/alc.h>

namespace ironengine
{
	struct Audio;

	/// @brief Struct that outputs sound, inherits from component
	struct SoundSource : Component
	{
	private:
		/// @brief The raw audio data
		std::weak_ptr<Audio> m_audio;

	public:
		/// @brief Basic constructor for the SoundSource component
		SoundSource();
		/// @brief Play the sound that the soundsource has
		void play();
		/// @brief Function that is called every tick allowing constant updates
		void onTick();
		/// @brief Allows the audio file to be set via the resource system
		/// @param _audio The audio file from the resource system
		void setAudio(std::shared_ptr<Audio> _audio);
	};
}