#include "Camera.h"

namespace vge {

#define PI 3.141592
	
	Camera::Camera()
	{
		this->projectionMatrix = glm::perspective<float>(glm::radians(2 * PI), 100 / 100, 0.0f, 10.0f);
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
	}

};