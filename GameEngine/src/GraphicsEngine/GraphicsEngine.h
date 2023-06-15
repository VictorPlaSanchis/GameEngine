#pragma once
#include "../Object/Component.h"
#include "Shader.h"
#include "../Object/Components/Model.h"
#include "../SceneSystem/Scene.h"

#include <vector>
#include <unordered_map>

#include "../GLM/glm/glm.hpp"
#include "./DrawableObject.h"
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

		std::unordered_map<std::string, Model*> modelContainer;
		std::unordered_map<std::string, unsigned int> textureContainer;
		std::unordered_map<std::string, Shader*> shaderContainer;
		std::unordered_map<std::string, unsigned int> programShaderContainer;

		std::vector<DrawableObject*> drawableObjects;

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind(unsigned int shaderProgram = 0);
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

		Model* getModel(std::string modelPath);
		unsigned int getTexture(std::string texturePath);
		unsigned int getShaderProgram(std::string shaderProgramName);
		unsigned int createVAO(std::string modelPath, std::string texturePath, unsigned int* textureId);
		DrawableObject* existDrawableObject(std::string modelPath, unsigned int VAO, unsigned int shaderProgram, unsigned int textureId);
		DrawableObject* createDrawableObject(std::string modelPath, std::string texturePath, std::string shaderProgramName);

		Shader* InitShader(const char* filename);
		unsigned int CreateProgram(std::string nameProgram, std::vector<const char*> filenames);
		void passUniform(unsigned int programShader, std::vector<float> data, const char* uniformName);
		void passUniform(unsigned int programShader, glm::vec4 data, const char* uniformName);
		void passUniformMat4(unsigned int programShader, std::vector<std::vector<float> > mat, const char* uniformName);
		void passUniformMat4(unsigned int programShader, glm::mat4 mat, const char* uniformName);
		unsigned int pushModel(Model* model, unsigned int programAssigned = -1);
		unsigned int pushTexture(const char* filename);
		void DrawData();
		void CleanData();
		void setDrawableObject(DrawableObject* drawableObject);

	};

#define GraphicsEngineVGE (*(GraphicsEngine::get()))

}

