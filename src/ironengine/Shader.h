#include "Resource.h"
#include <memory>
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that holds a frag and vertex shader
	struct Shader : Resource
	{
	private:
		/// @brief The raw data for the shaders
		std::shared_ptr<rend::Shader> m_shader;
		/// @brief Path to the vertex shader
		std::string m_vertPath;
		/// @brief Path to the fragment shader
		std::string m_fragPath;

	public:
		/// @brief Load the shader file using the path
		void onLoad();

		/// @brief Get the raw data for the shader file
		/// @return The shader in the rend::Shader format
		std::shared_ptr<rend::Shader> getRaw();
	};
}