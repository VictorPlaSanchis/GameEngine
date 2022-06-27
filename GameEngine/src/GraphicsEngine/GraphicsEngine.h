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
	    std::string getSourceShader(const char* pathShader);

		std::unordered_map<unsigned int, Model*> models;
		std::unordered_map<unsigned int, unsigned int> textures;
		std::unordered_map<unsigned int, unsigned int> shaders;

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind(unsigned int shaderProgram = 0);
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

		Shader* InitShader(const char* filename);
		unsigned int CreateProgram(std::vector<const char*> filenames);
		void passUniform(unsigned int programShader, std::vector<float> data, const char uniformName[]);
		unsigned int pushModel(Model* model, unsigned int programAssigned = -1);
		void pushTexture(const char* filename, unsigned int VAO);
		void DrawData();
		void LinkShader(unsigned int VAO, unsigned int ShaderProgramID);

	};

}

