#include "BoxCollider.h"
#include "Entity.h"
#include "Transform.h"

namespace ironengine
{
	// Called once when the box collider is created, servers as a makeshift constructor 
	void BoxCollider::onInit(glm::vec3 _size, glm::vec3 _offset, bool _static)
	{
		m_size = _size;
		m_offset = _offset;
		m_static = _static;
	}

	glm::vec3 BoxCollider::getSize()
	{
		return m_size;
	}

	glm::vec3 BoxCollider::getOffset()
	{
		return m_offset;
	}

	bool BoxCollider::getStatic()
	{
		return m_static;
	}

	bool BoxCollider::colliding(BoxCollider& _other)
	{
		// Declare local variables
		glm::vec3 a = getParent()->getTransform()->getPosition() + m_offset;
		glm::vec3 b = _other.getParent()->getTransform()->getPosition() + _other.m_offset;
		glm::vec3 ahs = m_size / 2.0f;
		glm::vec3 bhs = _other.m_size / 2.0f;

		// Check for overlaps on the x axis
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
		// Check for overlaps on the y axis
		if (a.y > b.y)
		{
			if (b.y + bhs.y < a.y - ahs.y)
			{
				return false;
			}
		}
		else
		{
			if (a.y + ahs.y < b.y - bhs.y)
			{
				return false;
			}
		}
		// Check for overlaps on the z axis
		if (a.z > b.z)
		{
			if (b.z + bhs.z < a.z - ahs.z)
			{
				return false;
			}
		}
		else
		{
			if (a.z + ahs.z < b.z - bhs.z)
			{
				return false;
			}
		}

		// If nothing else has been detected return true
		return true;
	}
}