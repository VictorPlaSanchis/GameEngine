#pragma once

#include "Object.h"
#include "../GLM/glm/glm.hpp"
#include "../GLM/glm/gtc/matrix_transform.hpp"

namespace vge {

	enum CameraType {
		Perspective,
		Ortogonal,
		Isometric
	};

	class Camera : public Object
	{

	private:

		CameraType cameraType;
		Vector3F initialPosition;
		glm::mat4 projectionMatrix;

	public:

		Camera();
		~Camera();

		virtual void Update() override;

		glm::mat4 getProjectionMatrix() { return this->projectionMatrix; };

	};

};

