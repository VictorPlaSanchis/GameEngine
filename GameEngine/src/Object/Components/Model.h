#pragma once
#include <vector>
#include "../Component.h"
#include "../Transform.h"

namespace vge {

	class Model
	{
	
	private:
		
		std::vector<float> data;
		std::vector<float> dataColor;
		std::vector<float> dataTexCoord;
		std::vector<float> dataNormals;
		std::vector<unsigned int> dataIndexs;
		std::vector<unsigned int> dataColorIndexs;
		std::vector<unsigned int> dataTexCoordIndexs;
		std::vector<unsigned int> dataNormalsIndexs; 

		unsigned int numVertex;

	public:

		Model();
		Model(std::vector<float> vertexs);
		~Model();

		void assignVertexs(std::vector<float> model);
		void assignVertexsColor(std::vector<float> color);
		void assignVertexsTexCoord(std::vector<float> texCoord);
		void assignVertexsNormals(std::vector<float> normals);
		void assignVertexsIndexs(std::vector<unsigned int> modelIndexs);
		void assignVertexsColorIndexs(std::vector<unsigned int> colorIndexs);
		void assignVertexsTexCoordIndexs(std::vector<unsigned int> texCoordIndexs);
		void assignVertexsNormalsIndexs(std::vector<unsigned int> normalsIndexs);

		std::vector<float> getData();
		std::vector<float> getDataColor();
		std::vector<float> getDataTexCoord();
		std::vector<float> getDataNormals();
		std::vector<unsigned int> getDataIndexs();
		std::vector<unsigned int> getDataColorIndexs();
		std::vector<unsigned int> getDataTexCoordIndexs();
		std::vector<unsigned int> getDataNormalsIndexs(); 
		unsigned int getNumVertexs();

		void load(Model* modelToLoad);

	};

};