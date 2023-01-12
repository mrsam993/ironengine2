#include "Shader.h"
#include "Resource.h"

namespace ironengine
{
	void Shader::onLoad()
	{
		// Load the shader using the resource path
		m_shader = std::make_shared<rend::Shader>(std::string(getPath() + ".vert").c_str(), std::string(getPath() + ".frag").c_str());
	}

	std::shared_ptr<rend::Shader> Shader::getRaw()
	{
		return m_shader;
	}
}