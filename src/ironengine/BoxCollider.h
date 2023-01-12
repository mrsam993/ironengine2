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
		/// @brief If an object should move or not 
		bool m_static;

	public:
		/// @brief Initial setup for the box collider, only called once
		/// @param Size of the box collider
		/// @param Offset of the collider
		/// @param If the object can move
		void onInit(glm::vec3 _size, glm::vec3 _offset, bool _static);

		/// @brief Get data on the colliders size
		/// @retuen The colliders size
		glm::vec3 getSize();
		/// @brief Get data on the colliders offset
		/// @retuen The colliders offset
		glm::vec3 getOffset();
		/// @brief Get data on if the collider should move or not
		/// @retuen If the collider should move or not
		bool getStatic();

		/// @brief Check to see if a collision is happening
		/// @param _other The BoxCollider that we are checking collisions against
		/// @return If a collision has occured or not
		bool colliding(BoxCollider& _other);
	};
}