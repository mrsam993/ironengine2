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
		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->tick();
		}
	}

	void Entity::display()
	{
		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->display();
		}
	}

	void Entity::kill()
	{
		if (!m_alive) return;

		m_alive = false;

		for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin();
			it != m_components.end(); ++it)
		{
			(*it)->kill();
		}
	}
}