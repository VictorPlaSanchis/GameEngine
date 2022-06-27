#include "MyGameObject.h"
#include "../Log/Console.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/SpriteRenderer.h"
#include "../GraphicsEngine/Model.h"

namespace vge {

	MyGameObject::MyGameObject()
	{
		SpriteRenderer* sprite = this->addComponent<SpriteRenderer>("./imgs/tumblr.png");
		//GraphicsEngine::get()->passUniform(sprite->getShaderProgramLinked(), this->transform->getValues(), "transform");
	}

	MyGameObject::~MyGameObject()
	{
	}
}


