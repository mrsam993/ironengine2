#include "Resource.h"

namespace ironengine
{
	std::string Resource::getPath() const
	{
		return m_path;
	}

	void Resource::load()
	{
		onLoad();
	}
}