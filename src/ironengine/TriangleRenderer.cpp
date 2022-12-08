#include "TriangleRenderer.h"
#include "Core.h"
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Camera.h"

namespace ironengine
{
	TriangleRenderer::TriangleRenderer() :
		m_shader("../data/shaders/basic.vert", "../data/shaders/basic.frag")
	{
		m_mesh.loadQuad();
	}

	void TriangleRenderer::onTick()
	{
		auto transform = getParent()->getTransform();

		if (getCore()->getKeyboard()->GetKey(KeyCode::up))
		{
			transform->setScale(transform->getScale() * 1.05f);
		}

		if (getCore()->getKeyboard()->GetKey(KeyCode::down))
		{
			transform->setScale(transform->getScale() * 0.95f);
		}
	}

	void TriangleRenderer::onDisplay()
	{
		rend::Renderer r(640, 480);

		r.shader(&m_shader);
		r.mesh(&m_mesh);
		r.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		r.model(getParent()->getTransform()->getModelMatrix());
		r.color(m_color);

		r.render();
	}

	void TriangleRenderer::SetColor(float _r, float _g, float _b, float _a)
	{
		m_color = glm::vec4(_r, _g, _b, _a);
	}
}