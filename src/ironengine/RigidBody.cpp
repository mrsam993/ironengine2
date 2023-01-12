#include "RigidBody.h"
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
				if (i == y)
				{			
					if(collider1->colliding(*colliders.at(y)));
					{
						std::shared_ptr <BoxCollider> collider2 = colliders.at(y);
						onCollision(collider1, collider2);
					}
				}
			}
		}
	}

	void RigidBody::onCollision(std::shared_ptr <BoxCollider> collider1, std::shared_ptr <BoxCollider> collider2)
	{
		// Add later
	}
}