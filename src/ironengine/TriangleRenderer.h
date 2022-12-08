#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	/// @brief Struct that renders triangles, inherits from component
	struct TriangleRenderer : Component
	{
		// Friend declarations
		friend struct Entity;
	private:
		/// @brief Mesh of the triangle renderer
		rend::Mesh m_mesh;
		/// @brief Shader of the triangle renderer
		rend::Shader m_shader;
		/// @brief Color of the triangle renderer
		glm::vec4 m_color;

		/// @brief Function that is called every tick
		void onTick();
		/// @brief Function that is called when updating the display
		void onDisplay();

	public:
		/// @brief Basic constructor for triangle renderer
		TriangleRenderer();
		/// @brief Function to set the color of the displayed triangle
		/// @param _r Red channel
		/// @param _g Green channel
		/// @param _b Blue channel
		/// @param _a Alpha channel
		void SetColor(float _r, float _g, float _b, float _a);
	};
}