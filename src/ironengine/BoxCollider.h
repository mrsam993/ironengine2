#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that allows collision, inherits from component
	struct BoxCollider : Component
	{
	private:
		/// @brief Size of collider
		glm::vec3 m_size;
		/// @brief Offset of the collider from the transform component
		glm::vec3 m_offset;

	public:
		/// @brief Check to see if a collision is happening
		/// @param _other The BoxCollider that we are checking collisions against
		/// @return If a collision has occured or not
		bool colliding(BoxCollider& _other);
	};
}