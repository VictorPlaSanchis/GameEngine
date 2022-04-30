#include "MyGameObject.h"
#include "../Log/Console.h"

namespace vge{

	vge::MyGameObject::MyGameObject()
	{
		// Initialize Script component
		this->script = MyGameScript();


		// Initialize Sprite component
		this->sprite = SpriteRenderer();

		
		// Adding components
		this->addComponent(&script);
		this->addComponent(&sprite);

		// Adding object into current scene of the game
		SceneManagement::get()->getCurrentScene()->addObject(this);


		// Debugging transform object position and warning that the object have been created succesfully
		Console::debug("New object created...", Console::COLOR::CYAN, Console::SENDER::AUXILIAR);
		Console::debug("Transofrm X: " + std::to_string(this->transform->getValues()[0]), Console::COLOR::CYAN, Console::SENDER::AUXILIAR);
		Console::debug("Transofrm Y: " + std::to_string(this->transform->getValues()[1]), Console::COLOR::CYAN, Console::SENDER::AUXILIAR);
		Console::debug("Transofrm Z: " + std::to_string(this->transform->getValues()[2]), Console::COLOR::CYAN, Console::SENDER::AUXILIAR);

	}

	vge::MyGameObject::~MyGameObject()
	{
	}

}


