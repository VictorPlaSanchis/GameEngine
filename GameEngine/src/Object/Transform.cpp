#include "Transform.h"

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
	}

	void Transform::move(const Vector<double, 3>& direction)
	{
		this->values += direction;
	}


}