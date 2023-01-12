#include "Component.h"
#include "Transform.h"
#include <SDL2/SDL.h>
#include <rend/rend.h>

namespace ironengine
{
	// Forward declarations
	struct Transform;

	/// @brief Camera for the scene, inherits from component
	struct Camera : Component
	{
	private:		
		/// @brief Function that updates every tick allowing constant updates
		void onTick();

	public:
		/// @brief Basic constructor for camera
		Camera();
		/// @brief Detailed constructor for camera
		/// @param _fov Field of view in degrees
		/// @param _near Position of the near plane
		/// @param _far Position of the far plane
		Camera(float _fov, float _near, float _far);
		/// @brief Called on camera declaration, sets m_camera in core 
		void onInit();
		/// @brief Calculates and gets the view matrix from the model matrix
		/// @return View matrix as a mat4
		rend::mat4 getViewMatrix();

		/// @brief Field of view in degrees
		float m_fov;
		/// @brief Position of the near plane
		float m_nearPlane;
		/// @brief Position of the far plane
		float m_farPlane;
	};
}