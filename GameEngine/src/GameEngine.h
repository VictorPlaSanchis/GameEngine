#pragma once
#include "InputSystem/InputListener.h"

class GameEngine : public InputListener
{

public:

	GameEngine();
	~GameEngine();

	void update();

	virtual void onKeyDown(int keyCode) override;
	virtual void onKeyUp(int keyCode) override;

};

