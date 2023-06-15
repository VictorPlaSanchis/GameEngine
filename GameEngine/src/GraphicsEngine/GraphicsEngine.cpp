#include <GL/glew.h>
#include "GraphicsEngine.h"
#include "GLFW/glfw3.h"
#include <fstream>

#include "../SceneSystem/SceneManagement.h"

#include "../GLM/glm/gtc/matrix_transform.hpp"
#include "../GLM/glm/gtc/type_ptr.hpp"
#include "../GLM/glm/glm.hpp"
#include "ObjLoader.h"

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

		// Creation of basic shader programs
		this->CreateProgram(
			"spriteRendererProgram",
			{
				"./src/GraphicsEngine/Shaders/SpriteRendererVS.vert",
				"./src/GraphicsEngine/Shaders/SpriteRendererFS.frag"
			}
		);

	}

	unsigned int GraphicsEngine::CreateProgram(std::string nameProgram, std::vector<const char*> filenames)
	{
		unsigned int newProgramID = glCreateProgram();
		for (const char* shadername : filenames) {
			Shader* newshader = GraphicsEngine::get()->InitShader(shadername);
			glAttachShader(newProgramID, newshader->getID());
		}
		glLinkProgram(newProgramID);
		this->programShaderContainer.insert(std::make_pair(nameProgram, newProgramID));
		return newProgramID;
	}

	Model* GraphicsEngine::getModel(std::string modelPath) {
		std::unordered_map<std::string, Model*>::iterator it = this->modelContainer.find(modelPath);
		if (it != this->modelContainer.end()) return this->modelContainer[modelPath];
		else {
			Model* newModel = ObjLoader::loadObj(&modelPath[0]);
			this->modelContainer.insert(std::make_pair(modelPath, newModel));
			return newModel;
		}
	}

	unsigned int GraphicsEngine::getTexture(std::string texturePath) {
		std::unordered_map<std::string, unsigned int>::iterator it = this->textureContainer.find(texturePath);
		if (it != this->textureContainer.end()) return this->textureContainer[texturePath];
		else {
			unsigned int newTexture = pushTexture(&texturePath[0]);
			this->textureContainer.insert(std::make_pair(texturePath, newTexture));
			return newTexture;
		}
	}

	unsigned int GraphicsEngine::getShaderProgram(std::string shaderProgramName) {
		std::unordered_map<std::string, unsigned int>::iterator it = this->programShaderContainer.find(shaderProgramName);
		if (it != this->programShaderContainer.end()) return this->programShaderContainer[shaderProgramName];
		else return 0; // default shader program
	}

	unsigned int GraphicsEngine::createVAO(std::string modelPath, std::string texturePath, unsigned int* texture) {
		Model* model = this->getModel(modelPath);
		*texture = this->getTexture(texturePath);
		return this->pushModel(model);
	}

	DrawableObject* GraphicsEngine::existDrawableObject(std::string modelPath, unsigned int VAO, unsigned int shaderProgram, unsigned int textureId) {
		for (DrawableObject* dO : this->drawableObjects) {
			if (
				dO->modelPath == modelPath and
				dO->VAO == VAO and
				dO->ShaderProgram == shaderProgram and
				dO->TextureId == textureId
			) return dO;
		}
		return nullptr;
	}

	DrawableObject* GraphicsEngine::createDrawableObject(std::string modelPath, std::string texturePath, std::string shaderProgramName)
	{

		unsigned int textureId;
		unsigned int vao = this->createVAO(modelPath, texturePath, &textureId);
		unsigned int programShader = this->getShaderProgram(shaderProgramName);

		DrawableObject* alreadyExist = existDrawableObject(modelPath, vao, programShader, textureId);
		if (alreadyExist) return alreadyExist;

		DrawableObject* newDrawableObejct = new DrawableObject;
		newDrawableObejct->modelPath = modelPath;
		newDrawableObejct->VAO = vao;
		newDrawableObejct->ShaderProgram = programShader;
		newDrawableObejct->TextureId = textureId;
		return newDrawableObejct;
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
		std::string sourceCodeVertex = getSourceShader("./src/GraphicsEngine/Shaders/vs.vert");
		this->vertexShader = new Shader(GL_VERTEX_SHADER, sourceCodeVertex.c_str());
		this->vertexShader->Init("VS, Vertex Shader");

		// Create a new Fragment shader from the source code and compile it
		std::string sourceCodeFragment = getSourceShader("./src/GraphicsEngine/Shaders/fs.frag");
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

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// Vertex positions
		unsigned int vertexVBO;
		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3) * model->getNumVertexs(), &model->getData()[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
		
		// Vertex colors
		if (model->getDataColor().size() > 0) {
			unsigned int colorVBO;
			glGenBuffers(1, &colorVBO);
			glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3) * model->getNumVertexs(), &model->getDataColor()[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
		}

		// Vertex texCoord
		if (model->getDataTexCoord().size() > 0) {
			unsigned int texCoordVBO;
			glGenBuffers(1, &texCoordVBO);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 2) * model->getNumVertexs(), &model->getDataTexCoord()[0], GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glEnableVertexAttribArray(2);
		}

		// Vertex normals
		if (model->getDataNormals().size() > 0) {
			unsigned int normalsVBO;
			glGenBuffers(1, &normalsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3) * model->getNumVertexs(), &model->getDataNormals()[0], GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(3);
		}

		unsigned int indexsVBO;
		glGenBuffers(1, &indexsVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexsVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->getDataIndexs().size() * sizeof(unsigned int), &model->getDataIndexs()[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return VAO;
	}

	unsigned int GraphicsEngine::pushTexture(const char* filename)
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
			return 0;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return texture;
	}

	void GraphicsEngine::DrawData()
	{
		Camera* currentCamera = SceneManagementVGE.getCurrentScene()->getCameraScene();
		for(DrawableObject* drawableObject : drawableObjects) {

			unsigned int currentVAO = drawableObject->VAO;
			unsigned int shader = drawableObject->ShaderProgram;
			unsigned int texture = drawableObject->TextureId;
			glm::mat4 modelMatrix = drawableObject->transformMatrix;

			// ---------------------

			GraphicsEngineVGE.passUniformMat4(shader, currentCamera->getViewMatrix(), "view");
			GraphicsEngineVGE.passUniformMat4(shader, currentCamera->getProjectionMatrix(), "projection");
			GraphicsEngineVGE.passUniformMat4(shader, modelMatrix, "model");

			// ---------------------
			
			this->Bind(shader);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBindVertexArray(currentVAO);
			Model* modelToDraw = this->modelContainer[drawableObject->modelPath];
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(modelToDraw->getDataIndexs().size()), GL_UNSIGNED_INT, (void*)0);

		}
		this->Unbind();
		glBindVertexArray(0);
	}

	void GraphicsEngine::CleanData()
	{
		this->drawableObjects = std::vector<DrawableObject*>();
	}

	void GraphicsEngine::setDrawableObject(DrawableObject* drawableObject)
	{
		this->drawableObjects.push_back(drawableObject);
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