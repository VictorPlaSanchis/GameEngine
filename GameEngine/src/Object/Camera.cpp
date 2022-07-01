#include "Camera.h"
#include "../GameEngine.h"

namespace vge {

#define PI 3.141592f
	
	Camera::Camera()
	{
		this->zNear = 0.0f;
		this->zFar = 10.0f;
		this->projectionAngle = 65.0f; // 35mm camera
		this->initialPosition = Vector3F({0.0f, 0.0f, 3.0f});
		this->projectionMatrix = glm::perspective( 
			this->projectionAngle * (PI / 180.0f), 
			GameEngineVGE.getAspect(),
			this->zNear, 
			this->zFar
		);
	}

	Camera::Camera(Vector3F initialPosition)
	{
		this->zNear = 0.0f;
		this->zFar = 10.0f;
		this->projectionAngle = 65.0f; // 35mm camera
		this->initialPosition = initialPosition;
		this->projectionMatrix = glm::perspective(
			this->projectionAngle * (PI / 180.0f),
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
			this->projectionAngle * (PI / 180.0f),
			GameEngineVGE.getAspect(),
			this->zNear,
			this->zFar
		); 
		return this->projectionMatrix;
	}

};