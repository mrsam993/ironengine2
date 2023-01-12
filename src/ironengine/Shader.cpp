#include "Shader.h"
#include "Resource.h"

namespace ironengine
{
	void Shader::onLoad()
	{
		// std::stringstream ss;
		// ss << int << float
		// ss.str().c_str();
		// Load the shader using the resource path
		m_shader = std::make_shared<rend::Shader>(std::string(getPath() + ".vert").c_str(), std::string(getPath() + ".frag").c_str()); //TODO THIS FOR MODEL, TEXTURE
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

//File paths from root and package
//high precisiion in frag shader
//main turn into function pointer mscripted_setloop
//https://github.com/osen/lre/tree/master/assets/models/entrance_hall