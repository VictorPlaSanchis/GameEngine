#pragma once
#include "Component.h"

namespace vge {

	class Transform : public Component
	{

	private:

		double x, y, z;

	public:

		Transform();
		~Transform();

	};


}
