#include "Camera.h"
#include "Transform.h"
#include "Core.h"
#include "Keyboard.h"

namespace ironengine
{
	Camera::Camera(float _fov, float _near, float _far) :
		m_fov(_fov),
		m_nearPlane(_near),
		m_farPlane(_far)
	{}

	// Default values for the camera 
	Camera::Camera() :
		m_fov(45.0f),
		m_nearPlane(0.1f),
		m_farPlane(100.0f)
	{}

	void Camera::onInit()
	{
		getCore()->m_camera = getParent()->getComponent<Camera>();
	}

	void Camera::onTick()
	{

	}

	rend::mat4 Camera::getViewMatrix()
	{
		return rend::inverse(getParent()->getTransform()->getModelMatrix());
	}
}