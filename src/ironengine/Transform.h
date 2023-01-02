#ifndef IRONENGINE_TRANSFORM_H
#define IRONENGINE_TRANSFORM_H

#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that allows the transformation of components
	struct Transform : public Component
	{
	private:
		/// @brief The position of a component
		glm::vec3 m_Position;
		/// @brief The rotation of a component
		glm::vec3 m_Rotation;
		/// @brief The scale of a component
		glm::vec3 m_Scale;
		/// @brief The model matrix of a component
		glm::mat4 m_ModelMatrix;
		/// @brief The translation matrix of a component
		glm::mat4 m_TranslationMatrix;
		/// @brief The rotation matrix of a component
		glm::mat4 m_RotationMatrix;
		/// @brief The scale matrix of a component
		glm::mat4 m_ScaleMatrix;
		/// @brief Checks if a transformation has been made
		bool m_Dirty;

	public:
		/// @brief Basic constructor for transform component
		Transform();

		/// @brief Get the current position of a component
		/// @return The current position
		glm::vec3 getPosition();
		/// @brief Set the position of a component using 3 separate axis
		/// @param _x Position on the X axis
		/// @param _y Position on the Y axis
		/// @param _z Position on the Z axis
		void setPosition(float _x, float _y, float _z);
		/// @brief Set the position of a component using 1 vector containing 3 axis
		/// @param _Position Position on all axis
		void setPosition(glm::vec3 _Position);

		void changePosition(float _x, float _y, float _z);

		/// @brief Get the current roation (without the ___) of a component
		/// @return The current roation without the ___ 
		glm::vec3 getRotation();
		/// @brief Set the rotation of a component using 3 separate axis
		/// @param _x Rotation on the X axis
		/// @param _y Rotation on the Y axis
		/// @param _z Rotation on the Z axis
		void setRotation(float _x, float _y, float _z);
		/// @brief Set the roation of a component using 1 vector containing 3 axis
		/// @param _Rotation Rotation on all axis
		void setRotation(glm::vec3 _Rotation);

		/// @brief Get the current roation (including the ___) of a component
		/// @return The current roation including the ___ 
		glm::quat getQRotation();
		/// @brief Set the quaternion rotation of a component using 4 separate axis
		/// @param _x Rotation on the X axis
		/// @param _y Rotation on the Y axis
		/// @param _z Rotation on the Z axis
		/// @param _w ___
		void setRotation(float _x, float _y, float _z, float _w);
		/// @brief Set the quaternion roation of a component using 1 vector containing 4 axis
		/// @param _Rotation Quaternion rotation on all axis
		void setRotation(glm::quat _Rotation);

		/// @brief Get the current scale of a component
		/// @return The current scale
		glm::vec3 getScale();
		/// @brief Set the scale of a component using 3 separate scales
		/// @param _x Scale on the X axis
		/// @param _y Scale on the Y axis
		/// @param _z Scale on the Z axis
		void setScale(float _x, float _y, float _z);
		/// @brief Set the scale of a component using 1 vector containing 3 separate scales
		/// @param _Scale
		void setScale(glm::vec3 _Scale);

		/// @brief Get the current model matrix of a component
		/// @return The current model matrix
		glm::mat4 getModelMatrix();
	};
}

#endif