#include "Object.h"
#include <functional>

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

	void Object::removeComponent(Component* component)
	{
		this->components.remove(component);
	}

	void Object::addChild(Object* child)
	{
		this->childs.push_back(child);
		std::function<void(Vector3F)>* moveCallback = new std::function<void(Vector3F)>(std::bind(&Transform::move, child->transform, std::placeholders::_1));
		std::function<void(float, Vector3F)>* rotateCallback = new std::function<void(float, Vector3F)>(std::bind(&Transform::rotate, child->transform, std::placeholders::_1, std::placeholders::_2));
		std::function<void(Vector3F)>* scaleCallback = new std::function<void(Vector3F)>([child](Vector3F scalar) {child->transform->scale(scalar);});

		this->transform->addCallback(
			moveCallback,
			rotateCallback,
			scaleCallback,
			nullptr
		);
		child->parent = this;
	}

	void Object::removeChild(Object* child)
	{
		this->childs.remove(child);
		child->parent = nullptr;
	}

	void Object::UpdateComponents()
	{
		for (Component* component : this->components) {
			component->Behaviour();
		}
		this->transform->Behaviour();	// ??? transform doesnt have any frame by frame behaviour

		// child updates
		for (Object* child : this->childs) {
			child->UpdateComponents();
			child->Update();
		}

	}


}