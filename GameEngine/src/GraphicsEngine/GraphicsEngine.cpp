#include "GraphicsEngine.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <fstream>

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
			Console::debug("Attacing id: " + std::to_string(newshader->getID()) + " to program: " + std::to_string(newProgramID), Console::COLOR::CYAN, Console::SENDER::GRAPHICS_ENGINE);
		}
		glLinkProgram(newProgramID);
		return newProgramID;
	}

	Shader* GraphicsEngine::InitShader(const char* filename) {
		// Create a new shader from the source code of filename and compile it
		Console::debug("Loading new shader: " + static_cast<std::string>(filename), Console::COLOR::CYAN, Console::SENDER::GRAPHICS_ENGINE);
		std::string sourceCode = getSourceShader(filename);
		int sizeName = static_cast<std::string>(filename).size();
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
		unsigned int VBO[3];

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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		this->models.insert(std::pair<unsigned int, Model*>(VAO, model));
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
			Console::debug("Failed to load texture.", Console::COLOR::RED, Console::SENDER::GRAPHICS_ENGINE);
			return;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		textures.insert(std::pair<unsigned int, unsigned int>(VAO, texture));
		stbi_image_free(data);
	}

	void GraphicsEngine::DrawData()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::unordered_map<unsigned int, Model*>::iterator it = this->models.begin();
		while (it != this->models.end()) {
			if (this->shaders.find(it->first) != this->shaders.end()) {
				this->Bind(this->shaders.find(it->first)->second);
			} else this->Bind();
			if (this->textures.find(it->first) != this->textures.end()) {
				glBindTexture(GL_TEXTURE_2D, textures[it->first]);
			}
			glBindVertexArray(it->first);
			glDrawArrays(GL_TRIANGLES, 0, it->second->getNumVertexs());
			it++;
			this->Unbind();
		}
		glBindVertexArray(0);
		glDisable(GL_BLEND);

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

}