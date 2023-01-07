#include "TriangleRenderer.h"
#include "Core.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"

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
		r.mesh(&m_mesh);
		r.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f)); //TODO GET THIS DATA FROM CAMERA REGISTER CAMERA WITH CORE, LIST OF CAMERAS IN CORE
		r.model(getParent()->getTransform()->getModelMatrix());
		r.view(getCore()->getCamera()->getViewMatrix());
		r.color(m_color);
		//rend::Texture* pt = m_texture.lock()->getRaw().get();
		//r.texture(m_texture.lock()->getRaw().get());
		
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
}