#include "Object.h"

Object::Object()
{
	components = {};
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

void Object::Update()
{
	for (Component* component : components) {
		component->Behaviour();
	}
}
