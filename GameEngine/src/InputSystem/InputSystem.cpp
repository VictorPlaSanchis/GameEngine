#include "InputSystem.h"

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::get()
{
	static InputSystem inputSystem;
	return &inputSystem;
}

void InputSystem::update()
{
	std::vector<InputListener*>::iterator it = listeners.begin();
	while (it != listeners.end()) {
		(*it)->refresh();
		it++;
	}
}

void InputSystem::addListener(InputListener* listener)
{
	listeners.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	std::vector<InputListener*>::iterator it = listeners.begin();
	while (it != listeners.end()) {
		if (*it == listener) {
			listeners.erase(it);
			return;
		}
	}
}