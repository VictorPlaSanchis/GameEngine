#include "Camera.h"
#include "../GameEngine.h"

namespace vge {

#ifndef PI
#define PI 3.14159265359
#endif
	
	Camera::Camera()
	{
		this->zNear = 0.1f;
		this->zFar = 10.0f;
		this->eyeTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionAngle = 65.0f; // 35mm camera
		this->initialPosition = Vector3F({0.0f, 0.0f, 3.0f});
		this->transform->move(initialPosition);
		this->projectionMatrix = glm::perspective( 
			this->projectionAngle * ((float)PI / 180.0f), 
			GameEngineVGE.getAspect(),
			this->zNear, 
			this->zFar
		);
	}

	Camera::Camera(Vector3F initialPosition)
	{
		this->zNear = 0.1f;
		this->zFar = 10.0f;
		this->eyeTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projectionAngle = 65.0f; // 35mm camera
		this->initialPosition = initialPosition;
		this->transform->move(initialPosition);
		this->projectionMatrix = glm::perspective(
			this->projectionAngle * ((float)PI / 180.0f),
			GameEngineVGE.getAspect(),
			this->zNear,
			this->zFar
		);
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		this->projectionMatrix = glm::perspective(
			this->projectionAngle * ((float)PI / 180.0f),
			GameEngineVGE.getAspect(),
			this->zNear,
			this->zFar
		); 
		return this->projectionMatrix;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		return glm::lookAt(this->transform->positionGLM(), this->eyeTarget, this->upVector);
	}

};