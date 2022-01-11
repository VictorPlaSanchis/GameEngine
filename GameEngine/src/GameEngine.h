#pragma once
#include <iostream>
#include "InputSystem/InputListener.h"

class GameEngine : public InputListener
{

public:

	GameEngine();
	~GameEngine();

	void Update();


	// Heredado vía InputListener
	virtual void onKeyDown(int keyCode) override;
	virtual void onKeyUp(int keyCode) override;

};

