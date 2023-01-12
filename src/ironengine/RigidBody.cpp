#include "RigidBody.h"
#include "BoxCollider.h"
#include "Core.h"

namespace ironengine
{
	void RigidBody::onTick()
	{
		std::vector <std::shared_ptr<BoxCollider> > colliders;
		getCore()->find<BoxCollider>(colliders);

		// Gather all colliders in the scene
		for (int i = 0; i < colliders.size(); i++)
		{
			std::shared_ptr <BoxCollider> collider1 = colliders.at(i);

			// Compare them against all other colliders
			for (int y = 0; y < colliders.size(); y++)
			{
				// Make sure a collider is not compared against itself
				if (i != y)
				{			
					if(collider1->colliding(*colliders.at(y)) == true)
					{
						std::shared_ptr <BoxCollider> collider2 = colliders.at(y);
						if (collider1->getStatic() != true)
						{
							onCollision(collider1, collider2);
						}
					}
				}
			}
		}
	}

	void RigidBody::onCollision(std::shared_ptr <BoxCollider> collider1, std::shared_ptr <BoxCollider> collider2)
	{
		// Declare local variables
		glm::vec3 col1Pos = collider1->getParent()->getTransform()->getPosition() + collider1->getOffset();
		glm::vec3 col2Pos = collider2->getParent()->getTransform()->getPosition() + collider2->getOffset();
		glm::vec3 colSize = collider1->getSize() + collider2->getSize();

		// Check if the collision is on the x axis
		if (col1Pos.x - col2Pos.x < colSize.x && col1Pos.x - col2Pos.x > -colSize.x)
		{
			// If the object is not static move it accordingly
			if (collider1->getStatic() == false)
			{
				collider1->getParent()->getTransform()->changePosition(0.0f, 0.0f, 0.1f);
			}

			// If the object is not static move it accordingly
			if (collider2->getStatic() == false)
			{
				collider2->getParent()->getTransform()->changePosition(0.0f, 0.0f, -0.1f);
			}
		}

		//// Check if the collision is on the y axis
		//if (col1Pos.y - col2Pos.y < colSize.y && col1Pos.y - col2Pos.y > -colSize.y)
		//{
		//	// If the object is not static move it accordingly
		//	if (collider1->getStatic() == false)
		//	{
		//		collider1->getParent()->getTransform()->changePosition(0.0f, 0.1f, 0.0f);
		//	}

		//	// If the object is not static move it accordingly
		//	if (collider2->getStatic() == false)
		//	{
		//		collider2->getParent()->getTransform()->changePosition(0.0f, -0.1f, 0.0f);
		//	}
		//}

		// Check if the collision is on the z axis
		if (col1Pos.z - col2Pos.z < colSize.z && col1Pos.z - col2Pos.z > -colSize.z)
		{
			// If the object is not static move it accordingly
			if (collider1->getStatic() == false)
			{
				collider1->getParent()->getTransform()->changePosition(0.0f, 0.0f, 0.1f);
			}

			// If the object is not static move it accordingly
			if (collider2->getStatic() == false)
			{
				collider2->getParent()->getTransform()->changePosition(0.0f, 0.0f, -0.1f);
			}
		}
	}
}