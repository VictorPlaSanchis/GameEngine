#pragma once

#include "../Object/Object.h"
#include "../Object/Components/SpriteRenderer.h"
#include "../Object/Components/Model.h"

namespace vge {

	class BlackSquare : public Object
	{

	private:

	public:

		BlackSquare();
		~BlackSquare();

		virtual void Update() override;

	};

}


