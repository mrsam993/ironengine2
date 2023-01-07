#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	struct Texture;

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
		/// @brief Texture of the triangle renderer
		std::weak_ptr<Texture> m_texture;

		/// @brief Function that is called every tick allowing constant updates
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
		void setColor(float _r, float _g, float _b, float _a);

		/// @brief Function to set the texture of the displayed triangle
		/// @param _texture The texture file
		void setTexture(std::shared_ptr<Texture> _texture);

		/// @brief The current angle of the triangle
		float m_angle = 0;
	};
}