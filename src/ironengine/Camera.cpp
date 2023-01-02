#include "Camera.h"
#include "Transform.h"
#include "Core.h"
#include "Keyboard.h"

namespace ironengine
{
	Camera::Camera(float _fov, float _near, float _far) :
		m_fov(_fov),
		m_nearPlane(_near),
		m_farPlane(_far),
		m_transform(std::make_shared<Transform>())
	{}

	Camera::Camera() :
		m_fov(45.0f),
		m_nearPlane(0.1f),
		m_farPlane(100.0f),
		m_transform(std::make_shared<Transform>())
	{}

	void Camera::onTick()
	{

	}
}