#include "Transform.h"

namespace ironengine
{
	// Default values for the transform component
	Transform::Transform() :
		m_ModelMatrix(glm::mat4(1.0f)),
		m_RotationMatrix(glm::mat4(1.0f)),
		m_TranslationMatrix(glm::mat4(1.0f)),
		m_ScaleMatrix(glm::mat4(1.0f)),
		m_Position(glm::vec3(0.0f)),
		m_Scale(glm::vec3(1.0f)),
		m_Rotation(glm::quat(glm::vec3(0.0f, 0.0f, 0.0f))),
		m_Dirty(true)
	{}


	rend::mat4 Transform::getModelMatrix()
	{
		// Declare local variables
		rend::mat4 rtn = rend::mat4(1.0f);
		rtn = rend::translate(rtn, m_Position);

		// Set the default scale and rotation of the models
		rtn = rend::rotate(rtn, rend::radians(m_Rotation.y), rend::vec3(0, 1, 0));
		rtn = rend::rotate(rtn, rend::radians(m_Rotation.x), rend::vec3(1, 0, 0));
		rtn = rend::rotate(rtn, rend::radians(m_Rotation.z), rend::vec3(0, 0, 1));
		rtn = rend::scale(rtn, m_Scale);

		return rtn;
	}

	// Get position
	glm::vec3 Transform::getPosition()
	{
		return m_Position;
	}
	// Set position to a definite value
	void Transform::setPosition(float _x, float _y, float _z)
	{
		m_Position = glm::vec3(_x, _y, _z);
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
		m_Dirty = true;
	}
	void Transform::setPosition(glm::vec3 _Position)
	{
		m_Position = _Position;
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), _Position);
		m_Dirty = true;
	}
	// Adjust position by changing a value
	void Transform::changePosition(float _x, float _y, float _z)
	{
		glm::mat4 model(1.0f);
		model = rend::rotate(model, rend::radians(m_Rotation.y), rend::vec3(0, 1, 0));
		model = rend::rotate(model, rend::radians(m_Rotation.x), rend::vec3(1, 0, 0));
		model = rend::rotate(model, rend::radians(m_Rotation.z), rend::vec3(0, 0, 1));
		glm::vec3 fwd(_x, _y, _z);
		fwd = glm::vec3(model * glm::vec4(fwd, 1.0f));
		m_Position += fwd;
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), m_Position);
		m_Dirty = true;
	}
	void Transform::changePosition(glm::vec3 _Position)
	{
		m_Position += _Position;
		m_TranslationMatrix = glm::translate(glm::mat4(1.0f), _Position);
		m_Dirty = true;
	}

	// Get rotation
	glm::vec3 Transform::getRotation()
	{
		return glm::eulerAngles(m_Rotation);
	}
	// Set rotation to a definite value
	void Transform::setRotation(float _x, float _y, float _z)
	{
		m_Rotation = glm::quat(glm::vec3(_x, _y, _z));
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	void Transform::setRotation(glm::vec3 _Rotation)
	{
		m_Rotation = glm::quat(_Rotation);
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	// Adjust rotation by changing a value
	void Transform::changeRotation(float _x, float _y, float _z)
	{
		m_Rotation += glm::quat(glm::vec3(_x, _y, _z));
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	void Transform::changeRotation(glm::vec3 _Rotation)
	{
		m_Rotation += glm::quat(_Rotation);
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}

	// Get quaternion rotation
	glm::quat Transform::getQRotation()
	{
		return m_Rotation;
	}
	// Set quaternion rotation to a definite value
	void Transform::setQRotation(float _x, float _y, float _z, float _w)
	{
		m_Rotation = glm::quat(_x, _y, _z, _w);
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	void Transform::setQRotation(glm::quat _Rotation)
	{
		m_Rotation = _Rotation;
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	// Adjust quaternion rotation by changing a value
	void Transform::changeQRotation(float _x, float _y, float _z, float _w)
	{
		m_Rotation += glm::quat(_x, _y, _z, _w);
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}
	void Transform::changeQRotation(glm::quat _Rotation)
	{
		m_Rotation += _Rotation;
		m_RotationMatrix = glm::toMat4(m_Rotation);
		m_Dirty = true;
	}

	// Get scale
	glm::vec3 Transform::getScale()
	{
		return m_Scale;
	}
	// Set scale to a definite value
	void Transform::setScale(float _x, float _y, float _z)
	{
		m_Scale = glm::vec3(_x, _y, _z);
	}
	void Transform::setScale(glm::vec3 _Scale)
	{
		m_Scale = _Scale;
	}
	// Adjust scale by changing a value
	void Transform::changeScale(float _x, float _y, float _z)
	{
		m_Scale += glm::vec3(_x, _y, _z);
	}
	void Transform::changeScale(glm::vec3 _Scale)
	{
		m_Scale += _Scale;
	}
}