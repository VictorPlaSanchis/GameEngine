#pragma once
#include "Component.h"
#include "../Types/Vector.h"
#include <vector>

namespace vge {

	class Transform : public Component
	{

	private:

		Vector3F values;

	public:

		Transform();
		~Transform();

		void Behaviour() override;

		void move(const Vector3F& direction);

		std::vector<float> getValues() { return {values[0], values[1], values[2]}; }

	};


}