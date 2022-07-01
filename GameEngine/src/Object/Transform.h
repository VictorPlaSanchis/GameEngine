#pragma once
#include "Component.h"
#include <vector>
#include "../GLM/glm/ext/vector_float3.hpp"
#include "../Types/Vector.h"

namespace vge {

	class Transform : public Component
	{

	private:

		Vector3F values;

	public:

		Transform();
		~Transform();

		void Behaviour() override;

		void move(const Vector3F& direction);

		std::vector<float> getValues() { return {values[0], values[1], values[2]}; }
		glm::vec3 getValuesGLM() { return glm::vec3(values[0], values[1], values[2]); }

	};


}