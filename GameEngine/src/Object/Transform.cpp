#include "Transform.h"
#include "../InputSystem/InputSystem.h"

#include <iostream>

namespace vge {

	Transform::Transform()
		: values({ (double)0,(double)0,(double)0 })
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Behaviour()
	{

		if (InputSystem::get()->isKeyDown('A')) {
			move(Vector<double,3>(-0.0001,0.0,0.0));
		}
		if (InputSystem::get()->isKeyDown('S')) {
			move(Vector<double, 3>(0.0, -0.0001, 0.0));
		}
		if (InputSystem::get()->isKeyDown('W')) {
			move(Vector<double, 3>(0.0, 0.0001, 0.0));
		}
		if (InputSystem::get()->isKeyDown('D')) {
			move(Vector<double, 3>(0.0001, 0.0, 0.0));
		}
	}

	void Transform::move(const Vector<double, 3>& direction)
	{
		this->values += direction;
	}


}