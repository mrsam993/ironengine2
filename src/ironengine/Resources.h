#ifndef IRONENGINE_RESOURCES_H
#define IRONENGINE_RESOURCES_H

#include "Resource.h"
#include <memory>
#include <string>
#include <vector>

namespace ironengine
{
	/// @brief Struct that holds all individual resource components
	struct Resources
	{
	private:
		/// @brief Vector of all the resources
		std::vector<std::shared_ptr<Resource> > m_resources;

	public:
		/// @brief Loads any type of resource
		/// @param _path The path to the desired resource
		/// @return A shared pointer to the resource
		template <typename T>
		std::shared_ptr<T> load(const std::string& _path)
		{
			// Search for previously loaded resource
			for (size_t i = 0; i < m_resources.size(); i++)
			{
				// Return if nothing is found
				if (m_resources.at(i)->getPath() == _path)
				{
					return std::dynamic_pointer_cast<T>(m_resources.at(i));
				}
			}

			// Create new instance, construct it and add to cache
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_path = _path;
			rtn->load();
			m_resources.push_back(rtn);

			return rtn;
		}
	};
}

#endif