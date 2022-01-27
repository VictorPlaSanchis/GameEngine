#pragma once
#include <string>

namespace vge {

	class Shader
	{

	private:

		const char* sourceCode;
		unsigned int shaderType;
		unsigned int shaderID;

		void Compile();

	public:

		Shader();
		Shader(unsigned int shaderType, const char* pathSource);
		~Shader();

		void Init();
		unsigned int getID();
	
	};

}