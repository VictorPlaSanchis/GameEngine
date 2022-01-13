#pragma once
#include <GLFW/glfw3.h>

class InputListener
{

private:

	unsigned char keysState[256];

public:

	InputListener();
	~InputListener();

	void refresh();

};

