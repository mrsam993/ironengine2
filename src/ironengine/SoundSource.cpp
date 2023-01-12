#include "SoundSource.h"
#include "Entity.h"
#include "Audio.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
#include <stdexcept>

namespace ironengine
{
	// Called once when the sound source is created, servers as a makeshift constructor 
	void SoundSource::onInit(float _volume, float _pitch, bool _looping)
	{
		m_volume = _volume;
		m_pitch = _pitch;
		m_looping = _looping;
	}

	void SoundSource::play()
	{
		
	}

	bool SoundSource::playing()
	{
		ALenum state;
		alGetSourcei(m_audio.lock()->m_audio, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	void SoundSource::onTick()
	{
		// Get the transform position and apply it to the audio listener position
		glm::vec3 position = getParent()->getTransform()->getPosition();
		alSource3f(m_audio.lock()->m_audio, AL_POSITION, position.x, position.y, position.z);

		// Update volume and pitch
		alSourcef(m_audio.lock()->m_audio, AL_GAIN, m_volume);
		alSourcef(m_audio.lock()->m_audio, AL_PITCH, m_pitch);

		// If the audio is not playing and is supposed to loop, play the audio
		if (m_looping && !playing())
		{
			alSourcePlay(m_audio.lock()->m_audio);
		}
	}

	void SoundSource::setAudio(std::shared_ptr<Audio> _audio)
	{
		// Set the audio file from the resource system
		m_audio = _audio;
		
	}

	// Get volume
	float SoundSource::getVolume()
	{
		return m_volume;
	}
	// Set volume to a definite value
	void SoundSource::setVolume(float _volume)
	{
		m_volume = _volume;
	}
	// Adjust volume by changing a value
	void SoundSource::changeVolume(float _volume)
	{
		m_volume += _volume;
	}

	// Get pitch
	float SoundSource::getPitch()
	{
		return m_pitch;
	}
	// Set pitch to a definite value
	void SoundSource::setPitch(float _pitch)
	{
		m_pitch = _pitch;
	}
	// Adjust pitch by changing a value 
	void SoundSource::changePitch(float _pitch)
	{
		m_pitch += _pitch;
	}

	// Get looping
	float SoundSource::getLooping()
	{
		return m_looping;
	}
	// Set looping to a definite value
	void SoundSource::setLooping(float _looping)
	{
		m_looping = _looping;
	}
}