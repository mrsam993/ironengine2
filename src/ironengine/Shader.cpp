#include "Shader.h"
#include "Resource.h"

namespace ironengine
{
	void Shader::onLoad()
	{
		// Load the shader using the resource path
		m_shader = std::make_shared<rend::Shader>(getVertPath().c_str(), getFragPath().c_str());
	}

	std::shared_ptr<rend::Shader> Shader::getRaw()
	{
		return m_shader;
	}

	///
	std::string Shader::getVertPath()
	{
		return m_vertPath;
	}

	///
	std::string Shader::getFragPath()
	{
		return m_fragPath;
	}
}