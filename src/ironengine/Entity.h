#ifndef IRONENGINE_ENTITY_H
#define IRONENGINE_ENTITY_H

#include "Transform.h"
#include <memory>
#include <vector>
#include <stdexcept>

namespace ironengine
{
	// Forward declarations
	struct Core;
	struct Component;
	struct Transform;

	/// @brief Struct that helps manage components of the program
	struct Entity
	{
		// Friend declarations
		friend struct Core;

	private:
		/// @brief Pointer to the core, allows data to be passed up
		std::weak_ptr<Core> m_core;
		/// @brief Pointer to self, preventing self destruction
		std::weak_ptr<Entity> m_self;
		/// @brief Manages the destruction of the entity
		bool m_alive;
		/// @brief List of components held by the entity
		std::vector<std::shared_ptr<Component> > m_components;
		/// @brief Pointer to the transform component
		std::weak_ptr<Transform> m_transform;

	public:
		/// @brief Creation and declaration of components 
		/// @return Shared pointer of the component
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			// Create a shared pointer to the component linking it to the hierarchy
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_parent = m_self;
			// Add it to the list of components before returning it
			m_components.push_back(rtn);
			// Run the onInit function for components as they are created
			rtn->onInit();
			return rtn;
		}		

		/// @brief Creation and declaration of components with multiple arguments
		/// @return Shared pointer of the component
		template <typename T, typename... Args>
		std::shared_ptr<T> addComponent(Args&&... args)
		{
			// Create a shared pointer to the component linking it to the hierarchy
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_parent = m_self;
			// Add it to the list of components before returning it
			m_components.push_back(rtn);
			// Run the onInit function for components as they are created
			rtn->onInit(std::forward< Args >(args)...);
			return rtn;
		}

		/// @brief Search all components owned by the entity 
		/// @return Shared pointer of the component
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			// Loop through the components vector
			for (int i = 0; i < m_components.size(); i++)
			{
				// Create and return a shared pointer when one is found return it
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(m_components[i]);
				if(rtn)
				{ 
					return rtn;
				}
			}
			// If none are found something has gone wrong and return an error
			throw std::runtime_error("Failed to find specified component");
		}

		/// @brief Gets the pointer to the core
		/// @return Shared pointer to core
		std::shared_ptr<Core> getCore();

		/// @brief Gets a pointer to the transform component, allows easy calling of the transform component
		/// @return Shared pointer to transform component
		std::shared_ptr<Transform> getTransform();

		/// @brief Function that updates every tick allowing constant updates
		void tick();
		/// @brief Function that is called when updating the display
		void display();
		/// @brief Function that destroys the current entity
		void kill();	
	};
}

#endif