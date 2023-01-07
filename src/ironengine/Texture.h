#include "Resource.h"
#include <memory>
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that holds an individual texture
	struct Texture : Resource
	{
	private:
		/// @brief The raw data for the texture file
		std::shared_ptr<rend::Texture> m_texture;

	public:
		/// @brief Load the texture file using the path
		void onLoad();

		/// @brief Get the raw data for the texture file
		/// @return The texture in the rend::texture format
		std::shared_ptr<rend::Texture> getRaw();
	};
}