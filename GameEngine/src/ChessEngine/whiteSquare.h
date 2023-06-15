#pragma once

#include "../Object/Object.h"
#include "../Object/Components/SpriteRenderer.h"
#include "../Object/Components/Model.h"

namespace vge {

	class WhiteSquare : public Object
	{

	private:

	public:

		WhiteSquare();
		~WhiteSquare();

		virtual void Update() override;

	};

}


