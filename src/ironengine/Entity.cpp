#include "Entity.h"
#include "Component.h"

namespace ironengine
{
	std::shared_ptr<Core> Entity::getCore()
	{
		return m_core.lock();
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return m_transform.lock();
	}

	void Entity::tick()
	{
		// Loop through every component owned by the entity and call all of their tick functions  
		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->tick();
		}
	}

	void Entity::display()
	{
		// Loop through every component owned by the entity and call all of their display functions  
		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->display();
		}
	}

	void Entity::kill()
	{
		// Ensure kill is being called at the correct time
		if (!m_alive) return;
		m_alive = false;

		// Loop through every component owned by the entity and destory them
		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->kill();
		}
	}
}