#pragma once
#include "Component.h"
#include <vector>
#include "../GLM/glm/ext/vector_float3.hpp"
#include "../Types/Vector.h"

namespace vge {

	class Transform : public Component
	{

	private:

		Vector3F l_position;
		Vector3F l_rotation;
		Vector3F l_scale;

	public:

		Transform();
		~Transform();

		void Behaviour() override;

		void move(const Vector3F& direction);
		void rotate(const Vector3F& rotation);
		void scale(const Vector3F& scalar);

		Vector3F position() { return this->l_position; }
		std::vector<float> positionArr() { return {l_position[0], l_position[1], l_position[2]}; }
		glm::vec3 positionGLM() { return glm::vec3(l_position[0], l_position[1], l_position[2]); }
		Vector3F rotation() { return this->l_rotation; }
		std::vector<float> rotationArr() { return { l_rotation[0], l_rotation[1], l_rotation[2] }; }
		glm::vec3 rotationGLM() { return glm::vec3(l_rotation[0], l_rotation[1], l_rotation[2]); }
		Vector3F scale() { return this->l_scale; }
		std::vector<float> scaleArr() { return { l_scale[0], l_scale[1], l_scale[2] }; }
		glm::vec3 scaleGLM() { return glm::vec3(l_scale[0], l_scale[1], l_scale[2]); }

	};


}