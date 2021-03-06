#pragma once

#include "../Object/Object.h"
#include "../Object/Components/SpriteRenderer.h"
#include "../Object/Components/Model.h"

namespace vge {

	class MyGameObject : public Object
	{

	private:

		SpriteRenderer* sprite;
		Model* model;
		unsigned int ShaderProgramLinked;

	public:

		MyGameObject();
		~MyGameObject();

		virtual void Update() override;

	};

}


