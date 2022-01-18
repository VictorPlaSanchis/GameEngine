#pragma once

class InputSystem
{

private:

	unsigned char lastKeyState[256] = {};

public:

	InputSystem();
	~InputSystem();

	static InputSystem* get();

	bool isKeyPressed(int keyCode);
	bool isKeyDown(int keyCode);
	bool isKeyReleased(int keyCode);

};

