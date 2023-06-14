#include "Transform.h"

namespace vge {

	Transform::Transform()
		: l_position({ 0.0f, 0.0f, 0.0f }),
		  l_rotation({ 0.0f, 0.0f, 0.0f }),
		  l_scale(   { 1.0f, 1.0f, 1.0f }),
		  l_lookingTo({ 0.0f, 0.0f, 1.0f })
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Behaviour()
	{
		//l_lookingTo = l_rotation;
	}

	void Transform::move(const Vector3F& direction)
	{
		this->l_position += direction;
	}

	void Transform::rotate(float angles, Vector3F axis)
	{
		//this->l_lookingTo = l_rotation;
		this->l_rotation.rotate(angles, axis);
	}

	void Transform::scale(const Vector3F& scalar)
	{
		this->l_scale = scalar;
	}


}