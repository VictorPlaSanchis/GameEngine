#pragma once
#include "Component.h"
#include "../Types/Vector.h"

namespace vge {

	class Transform : public Component
	{

	private:

		Vector<double, 3> values;

	public:

		Transform();
		~Transform();

		void Behaviour() override;

		void move(const Vector<double, 3>& direction);

		Vector<double, 3> getValues() { return this->values; }

	};


}