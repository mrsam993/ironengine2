#include "SoundListener.h"
#include "Core.h"
#include "Entity.h"
#include "Audio.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
#include <stdexcept>

namespace ironengine
{
	void SoundListener::onInit()
	{
		glm::vec3 position = getParent()->getTransform()->getPosition();
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}

	void SoundListener::onTick()
	{
		// Get relative position and rotation
		glm::vec3 position = getParent()->getTransform()->getPosition();
		glm::vec3 upPosition = position * glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 forwardPosition = position * glm::vec3(0.0f, 0.0f, 1.0f);
		ALfloat rotation[6] = { forwardPosition.x, forwardPosition.y, forwardPosition.z, upPosition.x, upPosition.y,  upPosition.z };

		// Set relative position and rotation
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}
}