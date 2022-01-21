#pragma once
#include "Component.h"

namespace vge {

	class ExampleComponent : public Component
	{

	private:

		int value;

	public:

		ExampleComponent();
		~ExampleComponent();

		virtual void Behaviour() override;

	};



}