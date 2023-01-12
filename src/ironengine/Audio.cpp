#include "Audio.h"
#include "Resource.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "stb_vorbis.c"

namespace ironengine
{
	void load_ogg(const std::string& _path, std::vector<unsigned char>& _buffer, ALenum& _format, ALsizei& _freq)
	{
		// Declare local variables
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		// Get the samples of the file
		size_t samples = stb_vorbis_decode_filename(_path.c_str(), &channels, &sampleRate, &output);

		// If no samples are gathered then the file has failed to open
		if (samples == -1)
		{
			throw std::runtime_error("Failed to open file '" + _path + "' for decoding");
		}
		// Otherwise set the format and sample rate based on the number of samples
		if (channels < 2)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_MONO16;
			sampleRate *= 2;
		}

		// Resize the buffer based on the size and sample rate
		_buffer.resize(samples * channels * sizeof(short));
		memcpy(&_buffer.at(0), output, _buffer.size());
		_freq = sampleRate;
		free(output);
	}

	void Audio::onLoad()
	{
		// Declare local variables
		ALenum format = 0;
		ALsizei freq = 0;
		std::vector<unsigned char> bufferData;
		// Load the audio using the resource path
		load_ogg(std::string(getPath() + ".ogg").c_str(), bufferData, format, freq);

		// Assign various buffer to get audio data
		ALuint bufferId = 0;
		alGenBuffers(1, &bufferId);
		alBufferData(bufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
		ALuint sourceId = 0;
		alGenSources(1, &sourceId);

		// Get playable audio variable using the buffers
		alSourcei(sourceId, AL_BUFFER, bufferId);

		// Set m_audio to our usable data
		m_audio = sourceId;
	}

	ALuint Audio::getRaw()
	{
		return m_audio;
	}
}