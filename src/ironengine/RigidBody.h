#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	// Forward declarations
	struct BoxCollider;

	/// @brief Struct that detects collisions, inherits from component
	struct RigidBody : Component
	{
	public:
		/// @brief Function that is called every tick allowing constant updates
		void onTick();
		/// @brief Function that is called when a collision is detected
		void onCollision(std::shared_ptr <BoxCollider> collider1, std::shared_ptr <BoxCollider> collider2);
	};
}