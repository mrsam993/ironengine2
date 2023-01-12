#include "ModelRenderer.h"
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
	// Default values for the model
	ModelRenderer::ModelRenderer() :
		m_rawModel("../data/export/export.obj"),
		m_rawTexture("../data/export/export.jpg")
	{
		m_mesh.loadQuad();
	}

	void ModelRenderer::onTick()
	{

	}

	void ModelRenderer::onDisplay()
	{
		// Set the resolution on the render window
		rend::ModelRenderer r(640, 480);
		rend::Renderer* pr = &r;
		// Apply the setting and variables of the renderer
		r.shader(m_shader->getRaw().get());
		r.backfaceCull(true);
		r.depthTest(true);
		r.projection(rend::perspective(rend::radians(getCore()->getCamera()->m_fov), 1.0f, getCore()->getCamera()->m_nearPlane, getCore()->getCamera()->m_farPlane));
		pr->model(getParent()->getTransform()->getModelMatrix());
		r.view(getCore()->getCamera()->getViewMatrix());
		r.model(m_model.lock()->getRaw().get());
		r.texture(&m_rawTexture);
		//r.texture(m_texture.lock()->getRaw().get());
		// Render thE model
		r.render();
	}

	void ModelRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		// Set the texture using the resource system
		m_texture = _texture;
	}

	void ModelRenderer::setModel(std::shared_ptr<Model> _model)
	{
		// Set the model using the resource system
		m_model = _model;
	}

	void ModelRenderer::setShader(std::shared_ptr<Shader> _shader)
	{
		// Set the shader using the resource system
		m_shader = _shader;
	}
}