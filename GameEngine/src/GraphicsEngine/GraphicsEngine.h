#pragma once
#include "../Object/Component.h"
#include "Shader.h"

namespace vge {

	class GraphicsEngine
	{

	private:

		unsigned int shaderProgram;
		Shader* vertexShader;
		Shader* fragmentShader;

		void InitShaders();
		void InitShaderProgram();
	    std::string getSourceShader(const std::string pathShader);
		

	public:

		GraphicsEngine();
		~GraphicsEngine();

		static GraphicsEngine* get();

		void Init();
		void Bind();
		void Unbind();
		unsigned int programID() { return this->shaderProgram; }

	};

}

