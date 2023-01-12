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
		/// @brief Audio volume
		float m_volume;
		/// @brief Audio pitch
		float m_pitch;
		/// @brief If the audio should play once or multiple times
		bool m_looping;

	public:
		/// @brief Basic constructor for the SoundSource component
		SoundSource();
		/// @brief Detailed constructor for camera
		/// @param _volume Volume of the audio
		/// @param _pitch Pitch of the audio
		/// @param _looping If the audio should loop or not
		SoundSource(float _volume, float _pitch, bool _looping);
		//void onInit();
		void onInit(float _volume);

		/// @brief Play the sound that the soundsource has
		void play();
		/// @brief Check if the sound is already playing
		bool playing();
		/// @brief Function that is called every tick allowing constant updates
		void onTick();
		/// @brief Allows the audio file to be set via the resource system
		/// @param _audio The audio file from the resource system
		void setAudio(std::shared_ptr<Audio> _audio);

		/// @brief Get the current volume
		/// @return the current volume
		float getVolume();
		/// @brief Set the current volume to a definite value
		/// @param The volume of the audio
		void setVolume(float _volume);
		/// @brief change the current volume
		/// @param The change of volume for the audio
		void changeVolume(float _volume);

		/// @brief Get the current pitch 
		/// @return the current pitch
		float getPitch();
		/// @brief Set the current pitch to a definite value
		/// @param The pitch of the audio
		void setPitch(float _pitch);
		/// @brief change the current pitch
		/// @param The change of pitch for the audio
		void changePitch(float _pitch);

		/// @brief Get the current looping value 
		/// @return the current looping value
		float getLooping();
		/// @brief Set the current audio to loop or not
		/// @param The looping value of the audio
		void setLooping(float _looping);
	};
}