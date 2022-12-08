#ifndef IRONENGINE_COMPONENT_H
#define IRONENGINE_COMPONENT_H

#include <memory>
#include <vector>

namespace ironengine
{
	// Forward declarations
	struct Entity;
	struct Core;
	struct Transform;
	class Keyboard;

	/// @brief Basic component struct that other classes will inherit from
	struct Component
	{
	private:
		friend struct Entity;

		/// @brief Function that is called every tick
		virtual void onTick();
		/// @brief Function that is called when updating the display
		virtual void onDisplay();
		/// @brief Function that destroys the current component
		virtual void onKill();

		/// @brief Called before onTick
		void tick();
		/// @brief Called before onDisplay
		void display();
		/// @brief Called before onKill
		void kill();

		/// @brief Pointer to the core, allows data to be passed up
		std::weak_ptr<Core> m_core;
		/// @brief Pointer to the entity, allows data to be passed up
		std::weak_ptr<Entity> m_parent;
		/// @brief Pointer to the keyboard, allows data to be passed up
		std::weak_ptr<Keyboard> m_keyboard;

	public:
		/// @brief Gets the pointer to the core
		/// @return Shared pointer to core
		std::shared_ptr<Core> getCore();
		/// @brief Gets the pointer to the entity
		/// @return Shared pointer to parent
		std::shared_ptr<Entity> getParent();
		/// @brief Gets the pointer to the keyboard
		/// @return Shared pointer to keyboard
		std::shared_ptr<Keyboard> getKeyboard();
	};
}

#endif