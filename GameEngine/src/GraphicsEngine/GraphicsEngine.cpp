#include "GraphicsEngine.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <fstream>

#include "../Log/Console.h"

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

	void GraphicsEngine::pushVAOData(std::vector<float>* data, int dimensionData)
	{
		unsigned int newVAO;
		VAO_DATA VAOData;
		VAOData.dataSize = data->size() / dimensionData;
		VAOData.dimensionSize = dimensionData;
		glGenBuffers(1, &newVAO);
		VAOs.push_back(newVAO);
		VAOsData.insert(std::pair<unsigned int, VAO_DATA>(newVAO, VAOData));
		glBindBuffer(GL_ARRAY_BUFFER, newVAO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(*data), &(*data)[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GraphicsEngine::resetVAOs() 
	{
		VAOs = std::vector<unsigned int>(0);
	}

	void GraphicsEngine::DrawData()
	{

		this->Bind();

		for (int i = 0; i < VAOs.size(); i++) {
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, VAOs[i]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);
		}

		resetVAOs();
		this->Unbind();

	}

}