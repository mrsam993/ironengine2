#include "SoundSource.h"
#include "Entity.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "stb_vorbis.c"

namespace ironengine
{
	void load_ogg(const std::string& _path, std::vector<unsigned char>& _buffer,
		ALenum& _format, ALsizei& _freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename(_path.c_str(),
			&channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::runtime_error("Failed to open file '" + _path + "' for decoding");
		}

		if (channels < 2)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_MONO16;
			sampleRate *= 2;
		}

		_buffer.resize(samples * channels * sizeof(short));
		memcpy(&_buffer.at(0), output, _buffer.size());

		_freq = sampleRate;

		free(output);
	}

	SoundSource::SoundSource()
	{
		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<unsigned char> bufferData;
		load_ogg("../data/dixie_horn.ogg", bufferData, format, freq);

		ALuint bufferId = 0;
		alGenBuffers(1, &bufferId);

		alBufferData(bufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);

		ALuint sourceId = 0;
		alGenSources(1, &sourceId);

		alSourcei(sourceId, AL_BUFFER, bufferId);

		//MOVE HERE?

		alSourcePlay(sourceId);
	}

	void SoundSource::onTick()
	{	
		//SHOULD THIS BE HERE?
		glm::vec3 position = getParent()->getTransform()->getPosition();
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}
}