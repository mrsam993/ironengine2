#include "Keyboard.h"

namespace ironengine
{
	Keyboard::Keyboard()
	{
		m_quit = false;
	}

	void Keyboard::Update()
	{

	}

	bool Keyboard::GetKey(int _key) const
	{
		for (size_t i = 0; i < m_keys.size(); ++i)
		{
			if (m_keys.at(i) == _key) return true;
		}

		return false;
	}

	bool Keyboard::GetKeyDown(int _key) const
	{
		for (size_t i = 0; i < m_keysDown.size(); ++i)
		{
			if (m_keysDown.at(i) == _key) return true;
		}

		return false;
	}

	bool Keyboard::GetKeyUp(int _key) const
	{
		for (size_t i = 0; i < m_keysUp.size(); ++i)
		{
			if (m_keysUp.at(i) == _key) return true;
		}

		return false;
	}
}