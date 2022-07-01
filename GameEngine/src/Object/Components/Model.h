#pragma once
#include <vector>
#include "../Component.h"

namespace vge {

	class Model : public Component
	{
	
	private:

		const char* texturePath;
		std::vector<float> data;
		std::vector<float> dataColor;
		std::vector<float> dataTexCoord;
		unsigned int numVertex;
		unsigned int VAOassigned;

	public:

		Model();
		Model(std::vector<float> vertexs);
		~Model();

		void assignVertexs(std::vector<float> model);
		void assignVertexsColor(std::vector<float> color);
		void assignVertexsTexCoord(std::vector<float> texCoord);
		void assignTexture(const char* filename);
		void setVAOassigned(unsigned int VAO);

		std::vector<float> getData();
		std::vector<float> getDataColor();
		std::vector<float> getDataTexCoord();
		const char* getTexturePath();
		unsigned int getNumVertexs();

		void Behaviour() override;

	};

};