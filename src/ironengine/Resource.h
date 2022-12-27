#ifndef IRONENGINE_RESOURCE_H
#define IRONENGINE_RESOURCE_H

#include <string>

namespace ironengine
{
	struct Resources;

	/// @brief Struct that holds an individual resource i.e. textures or models 
	struct Resource 
	{
		virtual void onLoad() = 0;
		std::string getPath() const;

	private:
		friend struct Resources;

		std::string m_path;
		void load();
	};
}

#endif