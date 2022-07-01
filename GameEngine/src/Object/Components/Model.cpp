#include "Model.h"
#include "../../GraphicsEngine/GraphicsEngine.h"

namespace vge {

	Model::Model()
	{
		this->texturePath = nullptr;
	}

	Model::Model(std::vector<float> model)
	{
		this->data = model;
		this->numVertex = static_cast<unsigned int>(model.size()/3.0);
		this->dataColor = {};
		this->dataTexCoord = {};
		this->texturePath = nullptr;
	}

	Model::~Model()
	{
	}

	void Model::assignVertexs(std::vector<float> model)
	{
		this->data = model;
		this->numVertex = static_cast<unsigned int>(model.size()/3.0);
	}

	void Model::assignVertexsColor(std::vector<float> color)
	{
		this->dataColor = color;
	}

	void Model::assignVertexsTexCoord(std::vector<float> texCoord)
	{
		this->dataTexCoord = texCoord;
	}

	void Model::assignVertexsNormals(std::vector<float> normals)
	{
		this->dataNormals = normals;
	}

	void Model::assignVertexsIndexs(std::vector<unsigned int> modelIndexs)
	{
		this->dataIndexs = modelIndexs;
	}

	void Model::assignVertexsColorIndexs(std::vector<unsigned int> colorIndexs)
	{
		this->dataColorIndexs = colorIndexs;
	}

	void Model::assignVertexsTexCoordIndexs(std::vector<unsigned int> texCoordIndexs)
	{
		this->dataTexCoordIndexs = texCoordIndexs;
	}

	void Model::assignVertexsNormalsIndexs(std::vector<unsigned int> normalsIndexs)
	{
		this->dataNormalsIndexs = normalsIndexs;
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

	std::vector<float> Model::getDataNormals()
	{
		return this->dataNormals;
	}

	std::vector<unsigned int> Model::getDataIndexs()
	{
		return this->dataIndexs;
	}

	std::vector<unsigned int> Model::getDataColorIndexs()
	{
		return this->dataColorIndexs;
	}

	std::vector<unsigned int> Model::getDataTexCoordIndexs()
	{
		return this->dataTexCoordIndexs;
	}

	std::vector<unsigned int> Model::getDataNormalsIndexs()
	{
		return this->dataNormalsIndexs;
	}

	const char* Model::getTexturePath()
	{
		return this->texturePath;
	}

	unsigned int Model::getNumVertexs()
	{
		return this->numVertex;
	}

	void Model::setVAOassigned(unsigned int VAO) 
	{
		this->VAOassigned = VAO;
	}

	void Model::setBuffer(unsigned int buffer)
	{
		this->buffer = buffer;
	}

	unsigned int Model::getBuffer()
	{
		return this->buffer;
	}

	void Model::Behaviour()
	{
		GraphicsEngine::get()->setDrawableObject(this->VAOassigned);
	}

};