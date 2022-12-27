#include "Texture.h"
#include "Resource.h"

namespace ironengine
{
	void Texture::onLoad()
	{
		m_texture = std::make_shared<rend::Texture>(getPath().c_str());
	}

	std::shared_ptr<rend::Texture> Texture::getRaw()
	{
		return m_texture;
	}
}