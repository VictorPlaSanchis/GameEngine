#pragma once

#include "../Object/Component.h"

namespace vge {

	class MyGameScript : public Component
	{

	public:

		MyGameScript();
		~MyGameScript();

		void Behaviour() override;

	};

}

