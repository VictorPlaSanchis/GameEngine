#pragma once
#include "../Object/Component.h"
#include "Shader.h"
#include "Model.h"

#include <vector>
#include <unordered_map>

#include "../Log/Console.h"

namespace vge {

	class GraphicsEngine
	{

	private:

		unsigned int shaderProgram;
		Shader* vertexShader;
		Shader* fragmentShader;

		void InitShaders();
		void InitShaderProgram();
	    std::string getSourceShader(const std::string pathShader);

		std::unordered_map<unsigned int, Model*> models;
		std::unordered_map<unsigned int, unsigned int> textures;

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind();
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

		unsigned int a;

		void passUniform(unsigned int programShader, std::vector<float> data, const char uniformName[]);
		void pushModel(Model* model);
		void pushTexture(const char* filename, unsigned int VAO);
		void DrawData();

	};

}

