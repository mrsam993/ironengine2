#include "BoxCollider.h"

#include "Entity.h"
#include "Transform.h"

namespace ironengine
{
	bool BoxCollider::colliding(BoxCollider& _other)
	{
		glm::vec3 a = getParent()->getTransform()->getPosition();
		glm::vec3 b = _other.getParent()->getTransform()->getPosition();
		glm::vec3 ahs = m_size / 2.0f;
		glm::vec3 bhs = _other.m_size / 2.0f;
		if (a.x > b.x)
		{
			if (b.x + bhs.x < a.x - ahs.x)
			{
				return false;
			}
		}
		else
		{
			if (a.x + ahs.x < b.x - bhs.x)
			{
				return false;
			}
		}
		// TODO: y
		// TODO: z
	}
}