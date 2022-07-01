#include "Shader.h"
#include "GL/glew.h"

#include "../Log/Console.h"

#include <iostream>
#include <vector>

namespace vge {

	void Shader::Compile(const char* shaderName)
	{

		glCompileShader(this->shaderID);
	    
		int compileInfo = 0;
		glGetShaderiv(this->shaderID, GL_COMPILE_STATUS, &compileInfo);

		if (compileInfo == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(this->shaderID, GL_INFO_LOG_LENGTH, &maxLength);
			char infoLog[1024];
			glGetShaderInfoLog(this->shaderID, maxLength, &maxLength, infoLog);
			glDeleteShader(this->shaderID);
			ConsoleErrorS(infoLog, GRAPHICS_ENGINE);
			ConsoleErrorS("Error on compiling shader, ID: " + std::to_string(this->shaderID) + ", Shader name: " + shaderName + ", Compile log : " + std::to_string(compileInfo), GRAPHICS_ENGINE);
			glDeleteShader(this->shaderID);
		}
		else {
			ConsoleDebugS((std::string)shaderName + " compiled succesfully!", GREEN, GRAPHICS_ENGINE);
		}

	}

	Shader::Shader()
	{
		this->sourceCode = nullptr;
		this->shaderType = 0;
	}

	Shader::Shader(unsigned int shaderType, const char* pathSource)
	{
		this->sourceCode = pathSource;
		this->shaderType = shaderType;
	}

	Shader::~Shader()
	{
	}

	void Shader::Init(const char* shaderName)
	{
		//glewExperimental = GL_TRUE;
		//glewInit(); // !!! ??? TODO revisar
		this->shaderID = glCreateShader(shaderType);
		glShaderSource(this->shaderID, 1, &sourceCode, NULL);
		this->Compile(shaderName);
	}

	unsigned int Shader::getID()
	{
		return this->shaderID;
	}

}

