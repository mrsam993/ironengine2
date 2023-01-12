#include "TriangleRenderer.h"
#include "Core.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"
#include "Shader.h"

namespace ironengine
{
	// Default values for the camera
	TriangleRenderer::TriangleRenderer() :
		m_shader("../data/shaders/basic.vert", "../data/shaders/basic.frag")
	{
		m_mesh.loadQuad();
	}

	void TriangleRenderer::onTick()
	{

	}

	void TriangleRenderer::onDisplay()
	{
		// Set the resolution on the render window
		rend::Renderer r(640, 480);
		// Apply the setting and variables of the renderer
		//r.backfaceCull(true);
		r.shader(&m_shader);	
		//r.shader(m_shader->getRaw());
		r.mesh(&m_mesh);
		r.projection(rend::perspective(rend::radians(getCore()->getCamera()->m_fov), 1.0f, getCore()->getCamera()->m_nearPlane, getCore()->getCamera()->m_farPlane));
		r.model(getParent()->getTransform()->getModelMatrix());
		r.view(getCore()->getCamera()->getViewMatrix());
		r.color(m_color);
		//rend::Texture* pt = m_texture.lock()->getRaw().get();
		//r.texture(m_texture.lock()->getRaw().get());

		//r.model(m_model.lock()->getRaw().get());
		
		r.render();
	}

	void TriangleRenderer::setColor(float _r, float _g, float _b, float _a)
	{
		// Set the color of the triangle externally
		m_color = glm::vec4(_r, _g, _b, _a);
	}

	void TriangleRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		// Set the texture using the resource system
		m_texture = _texture;
	}

	void TriangleRenderer::setModel(std::shared_ptr<Model> _model)
	{
		// Set the model using the resource system
		m_model = _model;
	}

	void TriangleRenderer::setShader(std::shared_ptr<Shader> _shader)
	{
		// Set the shader using the resource system
		//m_shader = _shader;
	}
}