#include "Resource.h"
#include <memory>
#include <AL/al.h>
#include <AL/alc.h>

namespace ironengine
{
	// Forward declarations
	struct SoundSource;

	/// @brief Struct that holds an individual audio file
	struct Audio : Resource
	{
		// Friend declarations
		friend struct SoundSource;

	private:
		/// @brief The raw data for the audio file
		ALuint m_audio;

	public:
		/// @brief Load the audio file
		void onLoad();

		/// @brief Get the raw data for the audio file
		/// @return The audio file in the ALuint format
		ALuint getRaw();
	};
}