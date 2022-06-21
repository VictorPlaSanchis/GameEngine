#include "Object.h"

#include "../Log/Console.h"

namespace vge {


	Object::Object()
	{
		this->components = {};
		this->childs = {};
		this->transform = new Transform();
	}

	Object::~Object()
	{
	}

	void Object::addComponent(Component* component)
	{
		this->components.push_back(component);
	}

	void Object::removeComponent(Component* component)
	{
		this->components.remove(component);
	}

	void Object::addChild(Object* child)
	{
		this->childs.push_back(child);
	}

	void Object::removeChild(Object* child)
	{
		this->childs.remove(child);
	}

	void Object::Update()
	{
		this->transform->Behaviour();	// ??? transform doesnt have any frame by frame behaviour
		for (Component* component : this->components) {
			component->Behaviour();
		}
	}


}