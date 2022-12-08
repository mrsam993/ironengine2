#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that renders triangles, inherits from component
	struct RigidBody : Component
	{
		virtual void onTick();
	};
}