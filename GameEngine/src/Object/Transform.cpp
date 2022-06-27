#include "Transform.h"
#include "../InputSystem/InputSystem.h"

#include <iostream>

namespace vge {

	Transform::Transform()
		: values({ (float)0,(float)0,(float)0 })
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Behaviour()
	{
	}

	void Transform::move(const Vector<float, 3>& direction)
	{
		this->values += direction;
	}


}