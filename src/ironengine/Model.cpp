#include "Model.h"
#include "Resource.h"

namespace ironengine
{
	void Model::onLoad()
	{
		// Load the model using the resource path
		m_model = std::make_shared<rend::Model>(std::string(getPath() + ".obj").c_str());
	}

	std::shared_ptr<rend::Model> Model::getRaw()
	{
		return m_model;
	}
}