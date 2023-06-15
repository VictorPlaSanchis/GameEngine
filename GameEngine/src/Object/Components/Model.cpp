#include "Model.h"
#include "../../GraphicsEngine/GraphicsEngine.h"
#include "../../SceneSystem/SceneManagement.h"

namespace vge {

	Model::Model()
	{
	}

	Model::Model(std::vector<float> model)
	{
		this->data = model;
		this->numVertex = static_cast<unsigned int>(model.size()/3.0);
		this->dataColor = {};
		this->dataTexCoord = {};
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

	unsigned int Model::getNumVertexs()
	{
		return this->numVertex;
	}

	void Model::load(Model* modelToLoad)
	{
		this->data = modelToLoad->data;
		this->dataIndexs = modelToLoad->dataIndexs;
		this->dataColor = modelToLoad->dataColor;
		this->dataColorIndexs = modelToLoad->dataColorIndexs;
		this->dataNormals = modelToLoad->dataNormals;
		this->dataNormalsIndexs = modelToLoad->dataNormalsIndexs;
		this->dataTexCoord = modelToLoad->dataTexCoord;
		this->dataTexCoordIndexs = modelToLoad->dataTexCoordIndexs;
		this->numVertex = static_cast<unsigned int>(this->data.size() / 3.0f);	
	}

};