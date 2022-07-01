#include "Transform.h"

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

	void Transform::move(const Vector3F& direction)
	{
		this->values += direction;
	}


}