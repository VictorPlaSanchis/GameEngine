#pragma once
#include "InputListener.h"
#include <vector>

class InputSystem
{

private:

	std::vector<InputListener*> listeners;

public:

	InputSystem();
	~InputSystem();

	static InputSystem* get();

	void update();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);

};

