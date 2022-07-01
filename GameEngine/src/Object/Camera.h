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

		float zNear, zFar, projectionAngle;

	public:

		Camera();
		Camera(Vector3F initialPosition);
		~Camera();

		virtual void Update() override;

		void setInitialPosition(Vector3F initialPosition) { this->initialPosition = initialPosition; }
		void setZNear(float value) { this->zNear = value; }
		void setZFar(float value) { this->zFar = value; }
		void setProjectionAngle(float value) { this->projectionAngle = value; }

		float getZNear() { return this->zNear; }
		float getZFar() { return this->zFar; }
		float getProjectionAngle() { return this->projectionAngle; }
		Vector3F getInitialPosition() { return this->initialPosition; }

		glm::mat4 getProjectionMatrix();

	};

};

