#pragma once
#include <string>

namespace vge {

	class DrawableObject {

	public:
		std::string modelPath;
		unsigned int VAO;
		unsigned int ShaderProgram;
		unsigned int TextureId;
		//std::function<glm::mat4()>* getModelMatrixTransformCallback;
		glm::mat4 transformMatrix;
	};
}
