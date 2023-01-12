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
		glm::quat m_Rotation;
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
		/// @brief Change the position of a component using 3 separate axis
		/// @param _x Change in position on the X axis
		/// @param _y Change in position on the Y axis
		/// @param _z Change in position on the Z axis
		void changePosition(float _x, float _y, float _z);
		/// @brief Change the position of a component using 1 vector containing 3 axis
		/// @param _Position Change in position on all axis
		void changePosition(glm::vec3 _Position);

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
		/// @brief Change the rotation of a component using 3 separate axis
		/// @param _x Change in rotation on the X axis
		/// @param _y Change in rotation on the Y axis
		/// @param _z Change in rotation on the Z axis
		void changeRotation(float _x, float _y, float _z);
		/// @brief Change the roation of a component using 1 vector containing 3 axis
		/// @param _Rotation Change in rotation on all axis
		void changeRotation(glm::vec3 _Rotation);

		/// @brief Get the current roation (including w) of a component
		/// @return The current roation including w 
		glm::quat getQRotation();
		/// @brief Set the quaternion rotation of a component using 4 separate axis
		/// @param _x Quaternion rotation on the X axis
		/// @param _y Quaternion rotation on the Y axis
		/// @param _z Quaternion rotation on the Z axis
		/// @param _w Quaternion rotation of w
		void setQRotation(float _x, float _y, float _z, float _w);
		/// @brief Set the quaternion roation of a component using 1 vector containing 4 axis
		/// @param _Rotation Quaternion rotation on all axis
		void setQRotation(glm::quat _Rotation);
		/// @brief Change the quaternion rotation of a component using 4 separate axis
		/// @param _x Change in quaternion rotation on the X axis
		/// @param _y Change in quaternion rotation on the Y axis
		/// @param _z Change in quaternion rotation on the Z axis
		/// @param _w Change in quaternion rotation of w
		void changeQRotation(float _x, float _y, float _z, float _w);
		/// @brief Change the quaternion roation of a component using 1 vector containing 4 axis
		/// @param _Rotation Change in quaternion rotation on all axis
		void changeQRotation(glm::quat _Rotation);

		/// @brief Get the current scale of a component
		/// @return The current scale
		glm::vec3 getScale();
		/// @brief Set the scale of a component using 3 separate scales
		/// @param _x Scale on the X axis
		/// @param _y Scale on the Y axis
		/// @param _z Scale on the Z axis
		void setScale(float _x, float _y, float _z);
		/// @brief Set the scale of a component using 1 vector containing 3 separate scales
		/// @param _Scale Scale on all axis
		void setScale(glm::vec3 _Scale);
		/// @brief Change the scale of a component using 3 separate scales
		/// @param _x Change in scale on the X axis
		/// @param _y Change in scale on the Y axis
		/// @param _z Change in scale on the Z axis
		void changeScale(float _x, float _y, float _z);
		/// @brief Change the scale of a component using 1 vector containing 3 separate scales
		/// @param _Scale Change in scale on all axis
		void changeScale(glm::vec3 _Scale);

		/// @brief Get the current model matrix of a component
		/// @return The current model matrix
		glm::mat4 getModelMatrix();
	};
}

#endif