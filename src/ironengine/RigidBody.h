#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that renders triangles, inherits from component
	struct RigidBody : Component
	{
	public:
		/// @brief Function that is called every tick allowing constant updates
		virtual void onTick();
	};
}