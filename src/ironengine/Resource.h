#ifndef IRONENGINE_RESOURCE_H
#define IRONENGINE_RESOURCE_H

#include <string>

namespace ironengine
{
	// Forward declarations
	struct Resources;

	/// @brief Struct that holds an individual resource i.e. textures or models 
	struct Resource 
	{
		// Friend declarations
		friend struct Resources;

	private:
		/// @brief The path to the resource
		std::string m_path;
		/// @brief Called before onLoad
		void load();

	public:
		/// @brief Resource management called after the resource is loaded
		virtual void onLoad() = 0;
		/// @brief Get the path to the resource
		/// @return A string of said path
		std::string getPath() const;
	};
}

#endif