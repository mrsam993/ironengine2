#ifndef IRONENGINE_ENTITY_H
#define IRONENGINE_ENTITY_H

#include <memory>
#include <vector>
#include "Transform.h"

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
		/// @tparam T The type of Component to be added
		/// @return Shared pointer of the component
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->m_parent = m_self;
			m_components.push_back(rtn);
			return rtn;
		}

		/// @brief Gets the pointer to the core
		/// @return Shared pointer to core
		std::shared_ptr<Core> getCore();

		/// @brief Gets a pointer to the transform component, allows easy calling of the transform component
		/// @return Shared pointer to transform component
		std::shared_ptr<Transform> getTransform();

		/// @brief Function that is called every tick
		void tick();
		/// @brief Function that is called when updating the display
		void display();
		/// @brief Function that destroys the current entity
		void kill();	
	};
}

#endif