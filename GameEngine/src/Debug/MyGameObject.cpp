#include "MyGameObject.h"
#include "../Log/Console.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../InputSystem/InputSystem.h"

namespace vge {

	MyGameObject::MyGameObject()
	{
		this->sprite = this->addComponent<SpriteRenderer>("./imgs/Megaman.png");
	}

	MyGameObject::~MyGameObject()
	{
	}

	void MyGameObject::Update()
	{
		float reductor = 1.0f / 2500.0f;
		if (this->transform->getValues()[1] > -0.5f) this->transform->move(DOWN * reductor);
		else if (InputSystem::get()->isKeyPressed(int('W'))) {
			Console::debug("JUMP!", Console::COLOR::CYAN, Console::SENDER::APPLICATION);
			this->transform->move(UP);
		}
		GraphicsEngine::get()->passUniform(this->sprite->getShaderProgramLinked(), this->transform->getValues(), "transform");
	}	

}


