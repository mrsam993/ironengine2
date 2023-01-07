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
	SoundSource::SoundSource()
	{
		
	}

	void SoundSource::play()
	{
		//TODO
	}

	void SoundSource::onTick()
	{	
		// Get the transform position and apply it to the audio listener position
		glm::vec3 position = getParent()->getTransform()->getPosition();
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}

	void SoundSource::setAudio(std::shared_ptr<Audio> _audio)
	{
		// Set the audio file from the resource system
		m_audio = _audio;
		alSourcePlay(m_audio.lock()->m_audio);
	}
}