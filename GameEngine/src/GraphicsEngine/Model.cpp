#include "Model.h"

namespace vge {

	Model::Model()
	{
		this->texturePath = nullptr;
	}

	Model::Model(std::vector<float> model) :
		data(model), numVertex(static_cast<unsigned int>(model.size())), dataColor({}), dataTexCoord({}), texturePath(nullptr)
	{
	}

	Model::~Model()
	{
	}

	void Model::assignVertexs(std::vector<float> model)
	{
		this->data = model;
		this->numVertex = static_cast<unsigned int>(model.size());
	}

	void Model::assignVertexsColor(std::vector<float> color)
	{
		this->dataColor = color;
	}

	void Model::assignVertexsTexCoord(std::vector<float> texCoord)
	{
		this->dataTexCoord = texCoord;
	}

	void Model::assignTexture(const char* filename)
	{
		this->texturePath = filename;
	}

	std::vector<float> Model::getData()
	{
		return this->data;
	}

	std::vector<float> Model::getDataColor()
	{
		return this->dataColor;
	}

	std::vector<float> Model::getDataTexCoord()
	{
		return this->dataTexCoord;
	}

	const char* Model::getTexturePath()
	{
		return this->texturePath;
	}

	unsigned int Model::getNumVertexs()
	{
		return this->numVertex;
	}

};