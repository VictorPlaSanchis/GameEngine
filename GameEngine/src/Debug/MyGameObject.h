#pragma once

#include "../Object/Object.h"
#include "MyGameScript.h"
#include "../SceneSystem/SceneManagement.h"
#include "../GraphicsEngine/SpriteRenderer.h"

namespace vge {

	class MyGameObject : public Object
	{

	private:

		MyGameScript script;
		SpriteRenderer sprite;

	public:

		MyGameObject();
		~MyGameObject();

	};

}


