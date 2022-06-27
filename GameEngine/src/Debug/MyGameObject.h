#pragma once

#include "../Object/Object.h"
#include "../Object/Components/SpriteRenderer.h"

namespace vge {

	class MyGameObject : public Object
	{

	private:

		SpriteRenderer* sprite;

	public:

		MyGameObject();
		~MyGameObject();

		virtual void Update() override;

	};

}


