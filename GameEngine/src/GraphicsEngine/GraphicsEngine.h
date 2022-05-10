#pragma once
#include "../Object/Component.h"
#include "Shader.h"

#include <vector>
#include <unordered_map>

namespace vge {

	class GraphicsEngine
	{

	private:

		struct VAO_DATA {
			unsigned int dataSize;
			unsigned int dimensionSize;
		};

		unsigned int shaderProgram;
		Shader* vertexShader;
		Shader* fragmentShader;

		void InitShaders();
		void InitShaderProgram();
	    std::string getSourceShader(const std::string pathShader);

		std::vector<unsigned int> VAOs;
		std::unordered_map<unsigned int, VAO_DATA> VAOsData;
		

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind();
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

		unsigned int a;

		void pushVAOData(std::vector<float>* data, int dimensionData);
		void resetVAOs();
		void DrawData();

	};

}

