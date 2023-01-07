#include "Resource.h"
#include <memory>
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that holds an individual model
	struct Model : Resource
	{
	private:
		/// @brief The raw data for the audio file
		std::shared_ptr<rend::Model> m_model;

	public:
		/// @brief Load the model file using the path
		void onLoad();

		/// @brief Get the raw data for the model file
		/// @return The model in the rend::Model format
		std::shared_ptr<rend::Model> getRaw();
	};
}