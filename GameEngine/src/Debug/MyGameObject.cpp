#include "MyGameObject.h"
#include "../Log/Console.h"

namespace vge {

	MyGameObject::MyGameObject()
	{
		// Initialize Script component
		this->script = MyGameScript();

		// Initialize Sprite component
		this->sprite = SpriteRenderer("./imgs/nya.bmp");

		// Adding components
		this->addComponent(&script);
		this->addComponent(&sprite);

		// Adding object into current scene of the game
		SceneManagement::get()->getCurrentScene()->addObject(this);
	}

	MyGameObject::~MyGameObject()
	{
	}

}


