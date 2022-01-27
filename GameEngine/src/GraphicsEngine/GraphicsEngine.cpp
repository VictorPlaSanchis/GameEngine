#include "GraphicsEngine.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "../Log/Log.h"
#include <fstream>

namespace vge {

	GraphicsEngine::GraphicsEngine()
	{
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		static GraphicsEngine graphicsEngine;
		return &graphicsEngine;
	}

	void GraphicsEngine::Init()
	{
		InitShaders();
		InitShaderProgram();
		DEBUG_GEL_WARNING("Graphics Engine initialized.");
	}

	void GraphicsEngine::InitShaders()
	{
		// Create a new Vertex shader from the source code and compile it
		std::string sourceCodeVertex = getSourceShader("./src/GraphicsEngine/vs.vert");
		this->vertexShader = new Shader(GL_VERTEX_SHADER, sourceCodeVertex.c_str());
		this->vertexShader->Init();

		// Create a new Fragment shader from the source code and compile it
		std::string sourceCodeFragment = getSourceShader("./src/GraphicsEngine/fs.frag");
		this->fragmentShader = new Shader(GL_FRAGMENT_SHADER, sourceCodeFragment.c_str());
		this->fragmentShader->Init();

	}
	void GraphicsEngine::InitShaderProgram()
	{
		this->shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, this->vertexShader->getID());
		glAttachShader(shaderProgram, this->fragmentShader->getID());
		glLinkProgram(shaderProgram);
	}

	std::string GraphicsEngine::getSourceShader(const std::string pathShader)
	{
		// Opening shader file
		std::string content, sourceCode;
		std::ifstream shaderFile;
		shaderFile.open(pathShader, std::ios_base::binary);
		if (!shaderFile) {
			DEBUG_GEL_ERROR("File on " + pathShader + " was not found.");
			return std::string("<SHADER NULL CONTENT>");
		}
		
		// Reading shader file content
		while (shaderFile.good()) {
			std::getline(shaderFile, content);
			sourceCode += content + '\n';
		}
		return sourceCode;
	}

	void GraphicsEngine::Bind()
	{
		glUseProgram(this->shaderProgram);
	}

	void GraphicsEngine::Unbind()
	{
		glUseProgram(0);
	}

}