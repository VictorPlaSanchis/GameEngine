#pragma once
#include "../Object/Component.h"
#include "Shader.h"
#include "../Object/Components/Model.h"
#include "../SceneSystem/Scene.h"

#include <vector>
#include <unordered_map>

#include "../GLM/glm/glm.hpp"
#include <set>

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
		std::unordered_map<unsigned int, std::string> shaders;
		std::unordered_map<std::string, unsigned int> programs;

		std::set<unsigned int> VAOsToDraw;

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind(unsigned int shaderProgram = 0);
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

		Shader* InitShader(const char* filename);
		unsigned int CreateProgram(std::string programName, std::vector<const char*> filenames);
		void passUniform(unsigned int programShader, std::vector<float> data, const char* uniformName);
		void passUniform(unsigned int programShader, glm::vec4 data, const char* uniformName);
		void passUniformMat4(unsigned int programShader, std::vector<std::vector<float> > mat, const char* uniformName);
		void passUniformMat4(unsigned int programShader, glm::mat4 mat, const char* uniformName);
		unsigned int pushModel(Model* model, unsigned int programAssigned = -1);
		unsigned int getShaderLinked(unsigned int VAO);
		void pushTexture(const char* filename, unsigned int VAO);
		void DrawData();
		void CleanData();
		void setDrawableObject(unsigned int VAO);
		void LinkShader(unsigned int VAO, std::string programName);

	};

#define GraphicsEngineVGE (*(GraphicsEngine::get()))

}

