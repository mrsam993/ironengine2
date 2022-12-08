#include <SDL2/SDL.h>
#include "Transform.h"

namespace ironengine
{
	// Forward declarations
	struct Transform;

	/// @brief Basic component struct that other classes will inherit from
	class Camera
	{
	private:

	public:
		/// @Brief Basic constructor for camera class
		Camera();
		/// @Brief Detailed constructor for camera class
		/// @param _fov Field of view in degrees
		/// @param _near Position of the near plane
		/// @param _far Position of the far plane
		Camera(float _fov, float _near, float _far);

		/// @brief Field of view in degrees
		float m_fov;
		/// @brief Position of the near plane
		float m_nearPlane;
		/// @brief Position of the far plane
		float m_farPlane;
		/// @brief Cameras transform component
		std::shared_ptr<Transform> m_transform;
	};
}