#pragma once
class InputListener
{

public:

	InputListener();
	~InputListener();

	virtual void onKeyDown(int keyCode) = 0;
	virtual void onKeyUp(int keyCode) = 0;
	virtual void onKeyPressed(int keyCode) = 0;

};

