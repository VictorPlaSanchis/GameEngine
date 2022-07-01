#include <GL/glew.h>
#include "GraphicsEngine.h"
#include "GLFW/glfw3.h"
#include <fstream>

#include "../SceneSystem/SceneManagement.h"

#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
		glewInit();
		InitShaders();
		InitShaderProgram();
	}

	unsigned int GraphicsEngine::CreateProgram(std::vector<const char*> filenames)
	{
		unsigned int newProgramID = glCreateProgram();
		for (const char* shadername : filenames) {
			Shader* newshader = GraphicsEngine::get()->InitShader(shadername);
			glAttachShader(newProgramID, newshader->getID());
		}
		glLinkProgram(newProgramID);
		return newProgramID;
	}

	Shader* GraphicsEngine::InitShader(const char* filename) {
		// Create a new shader from the source code of filename and compile it
		ConsoleDebugS("Loading new shader: " + static_cast<std::string>(filename), CYAN, GRAPHICS_ENGINE);
		std::string sourceCode = getSourceShader(filename);
		size_t sizeName = static_cast<std::string>(filename).size();
		std::string shaderType = static_cast<std::string>(filename).substr(sizeName-4, sizeName-1);
		Shader* newShader = new Shader();
		if (shaderType == "vert") newShader = new Shader(GL_VERTEX_SHADER, sourceCode.c_str());
		else if (shaderType == "frag") newShader = new Shader(GL_FRAGMENT_SHADER, sourceCode.c_str());
		newShader->Init(filename);
		return newShader;
	}

	void GraphicsEngine::InitShaders()
	{
		// Create a new Vertex shader from the source code and compile it
		std::string sourceCodeVertex = getSourceShader("./src/GraphicsEngine/vs.vert");
		this->vertexShader = new Shader(GL_VERTEX_SHADER, sourceCodeVertex.c_str());
		this->vertexShader->Init("VS, Vertex Shader");

		// Create a new Fragment shader from the source code and compile it
		std::string sourceCodeFragment = getSourceShader("./src/GraphicsEngine/fs.frag");
		this->fragmentShader = new Shader(GL_FRAGMENT_SHADER, sourceCodeFragment.c_str());
		this->fragmentShader->Init("FS, Fragment Shader");

	}
	void GraphicsEngine::InitShaderProgram()
	{
		this->shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, this->vertexShader->getID());
		glAttachShader(shaderProgram, this->fragmentShader->getID());

		glLinkProgram(shaderProgram);
	}

	std::string GraphicsEngine::getSourceShader(const char* pathShader)
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

	void GraphicsEngine::Bind(unsigned int shaderProgram)
	{
		if (shaderProgram > 0) glUseProgram(shaderProgram);
		else glUseProgram(this->shaderProgram);
	}

	void GraphicsEngine::Unbind()
	{
		glUseProgram(0);
	}

	unsigned int GraphicsEngine::pushModel(Model* model, unsigned int programAssigned)
	{
		unsigned int VAO;
		unsigned int VBO[4];

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, VBO);

		glBindVertexArray(VAO);

		// Vertex positions
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3) * model->getNumVertexs(), &model->getData()[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		
		// Vertex colors
		if (model->getDataColor().size() > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3) * model->getNumVertexs(), &model->getDataColor()[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
		}

		// Vertex texCoord
		if (model->getDataTexCoord().size() > 0 && model->getTexturePath() != nullptr) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 2) * model->getNumVertexs(), &model->getDataTexCoord()[0], GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(2);
			this->pushTexture(model->getTexturePath(), VAO);
		}
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->getDataIndexs().size() * sizeof(unsigned int), &model->getDataIndexs()[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->models.insert(std::pair<unsigned int, Model*>(VAO, model));
		model->setVAOassigned(VAO);
		model->setBuffer(VBO[3]);
		return VAO;
	}

	void GraphicsEngine::pushTexture(const char* filename, unsigned int VAO)
	{
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// load and generate the texture
		int width, height, nrChannels;
		unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
		
		if (!data) {
			ConsoleErrorS("Failed to load texture.", GRAPHICS_ENGINE);
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		textures.insert(std::pair<unsigned int, unsigned int>(VAO, texture));
		stbi_image_free(data);
	}

	void GraphicsEngine::DrawData()
	{

		std::set<unsigned int>::iterator it = this->VAOsToDraw.begin();
		while (it != this->VAOsToDraw.end()) {

			unsigned int currentVAO = *it;

			if (this->shaders.find(currentVAO) != this->shaders.end()) {
				this->Bind(this->shaders.find(currentVAO)->second);
			} else this->Bind();
			if (this->textures.find(currentVAO) != this->textures.end()) {
				glBindTexture(GL_TEXTURE_2D, textures[currentVAO]);
			}
			Model* modelToDraw = (this->models.find(currentVAO))->second;
			glBindVertexArray(currentVAO);
			glDrawElements(GL_TRIANGLES, modelToDraw->getDataIndexs().size(), GL_UNSIGNED_INT, (void*)0);
			it++;
			this->Unbind();

		}
		glBindVertexArray(0);

	}

	void GraphicsEngine::CleanData()
	{
		this->VAOsToDraw = std::set<unsigned int>();
	}

	void GraphicsEngine::setDrawableObject(unsigned int VAO)
	{
		this->VAOsToDraw.insert(VAO);
	}

	void GraphicsEngine::LinkShader(unsigned int VAO, unsigned int ShaderProgramID)
	{
		this->shaders.insert(std::pair<unsigned int, unsigned int>(VAO, ShaderProgramID));
	}

	void GraphicsEngine::passUniform(unsigned int programShader, std::vector<float> data, const char* uniformName)
	{
		this->Bind(programShader);
		GLuint loc = glGetUniformLocation(programShader, uniformName);
		switch (data.size()) {
			case 1:
				glProgramUniform1f(programShader, loc, data[0]);
				return;
			case 2:
				glProgramUniform2f(programShader, loc, data[0], data[1]);
				return;
			case 3:
				glProgramUniform3f(programShader, loc, data[0], data[1], data[2]);
				return;
			case 4:
				glProgramUniform4f(programShader, loc, data[0], data[1], data[2], data[3]);
				return;
		}
		this->Unbind();
	}

	void GraphicsEngine::passUniform(unsigned int programShader, glm::vec4 data, const char* uniformName)
	{
		this->Bind(programShader);
		GLuint loc = glGetUniformLocation(programShader, uniformName);
		glProgramUniform4f(programShader, loc, data[0], data[1], data[2], data[3]);
		this->Unbind();
	}

	void GraphicsEngine::passUniformMat4(unsigned int programShader, std::vector<std::vector<float> > mat, const char* uniformName)
	{
		this->Bind(programShader);
		GLuint loc = glGetUniformLocation(programShader, uniformName);
		glProgramUniformMatrix4fv(programShader, loc, 1, GL_FALSE, &mat[0][0]);
		this->Unbind();
	}

	void GraphicsEngine::passUniformMat4(unsigned int programShader, glm::mat4 mat, const char* uniformName)
	{
		this->Bind(programShader);
		GLuint loc = glGetUniformLocation(programShader, uniformName);
		glProgramUniformMatrix4fv(programShader, loc, 1, GL_FALSE, &mat[0][0]);
		this->Unbind();
	}

}