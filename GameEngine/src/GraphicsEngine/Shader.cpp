#include "Shader.h"
#include "GL/glew.h"

#include <iostream>

namespace vge {

	void Shader::Compile()
	{

		glCompileShader(this->shaderID);
	    
		int compileInfo = 0;
		glGetShaderiv(this->shaderID, GL_INFO_LOG_LENGTH, &compileInfo);
		
		if (compileInfo == GL_FALSE) {
			// Shader compile was unsuccesfull 
			glDeleteShader(this->shaderID);
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

	void Shader::Init()
	{
		glewExperimental = GL_TRUE;
		glewInit();
		this->shaderID = glCreateShader(shaderType);
		glShaderSource(this->shaderID, 1, &sourceCode, NULL);
		this->Compile();
	}

	unsigned int Shader::getID()
	{
		return this->shaderID;
	}

}

