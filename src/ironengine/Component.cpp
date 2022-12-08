#include "Component.h"
#include "Core.h"
#include "Entity.h"

namespace ironengine
{
	void Component::onTick() { }
	void Component::onDisplay() { }
	void Component::onKill() { }

	void Component::tick()
	{
		onTick();
	}

	void Component::display()
	{
		onDisplay();
	}

	void Component::kill()
	{
		onKill();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return getParent()->getCore();
	}

	std::shared_ptr<Entity> Component::getParent()
	{
		return m_parent.lock();
	}

	std::shared_ptr<Keyboard> Component::getKeyboard()
	{
		return getParent()->getCore()->getKeyboard();
	}
}