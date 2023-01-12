#include "Component.h"
#include <rend/rend.h>

namespace ironengine
{
	// Forward declarations
	struct Texture;
	struct Model;
	struct Shader;

	/// @brief Struct that renders models, inherits from component
	struct ModelRenderer : Component
	{
		// Friend declarations
		friend struct Entity;

	private:
		/// @brief Mesh of the model renderer
		rend::Mesh m_mesh;
		/// @brief Raw model of the model renderer
		rend::Model m_rawModel;
		/// @brief Raw texture of the model renderer
		rend::Texture m_rawTexture;
		/// @brief Shader of the model renderer
		std::shared_ptr<Shader> m_shader;
		/// @brief Texture of the model renderer
		std::weak_ptr<Texture> m_texture;
		/// @brief Model of the model renderer
		std::weak_ptr<Model> m_model;

		/// @brief Function that is called every tick allowing constant updates
		void onTick();
		/// @brief Function that is called when updating the display
		void onDisplay();

	public:
		/// @brief Basic constructor for model renderer
		ModelRenderer();

		/// @brief Function to set the texture of the displayed model
		/// @param _texture The texture file
		void setTexture(std::shared_ptr<Texture> _texture);
		/// @brief Function to set the model of the displayed model
		/// @param _model The model file
		void setModel(std::shared_ptr<Model> _model);
		/// @brief Function to set the shader of the displayed model
		/// @param _shader The shader file
		void setShader(std::shared_ptr<Shader> _shader);
	};
}