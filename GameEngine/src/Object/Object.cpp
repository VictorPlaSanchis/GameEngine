#include "Object.h"

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
		components.push_back(component);
	}

	void Object::removeComponent(Component* component)
	{
		components.remove(component);
	}

	void Object::addChild(Object* child)
	{
		childs.push_back(child);
	}

	void Object::removeChild(Object* child)
	{
		childs.remove(child);
	}

	void Object::Update()
	{
		transform->Behaviour();	// ??? transform doesnt have any frame by frame behaviour
		for (Component* component : components) {
			component->Behaviour();
		}
	}


}