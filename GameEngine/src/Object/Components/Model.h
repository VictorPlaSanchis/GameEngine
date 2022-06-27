#pragma once
#include <vector>
#include "../Component.h"

namespace vge {

	class Model : public Component
	{
	
	private:

		std::vector<float> data;
		std::vector<float> dataColor;
		std::vector<float> dataTexCoord;
		unsigned int numVertex;

		const char* texturePath;

	public:

		Model();
		Model(std::vector<float> vertexs);
		~Model();

		void assignVertexs(std::vector<float> model);
		void assignVertexsColor(std::vector<float> color);
		void assignVertexsTexCoord(std::vector<float> texCoord);
		void assignTexture(const char* filename);
		std::vector<float> getData();
		std::vector<float> getDataColor();
		std::vector<float> getDataTexCoord();
		const char* getTexturePath();
		unsigned int getNumVertexs();

		void Behaviour() override;

	};

};