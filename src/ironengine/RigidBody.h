#include "Component.h"
#include "BoxCollider.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that renders triangles, inherits from component
	struct RigidBody : Component
	{
	public:
		/// @brief Function that is called every tick allowing constant updates
		void onTick();
		/// @brief Function that is called when a collision is detected
		void onCollision(std::shared_ptr <BoxCollider> collider1, std::shared_ptr <BoxCollider> collider2);
	};
}