#include "Resource.h"
#include <memory>
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that holds an individual resource i.e. textures or models 
	struct Texture : Resource
	{
		void onLoad();

		std::shared_ptr<rend::Texture> getRaw();

	private:
		std::shared_ptr<rend::Texture> m_texture;
	};
}