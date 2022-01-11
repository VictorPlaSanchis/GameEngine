#include "GameEngine.h"
#include "InputSystem/InputSystem.h"
#include <iostream>

GameEngine::GameEngine()
{
	InputSystem::get()->addListener(this);
	InputSystem::get()->addListener(this);
}

GameEngine::~GameEngine()
{
	InputSystem::get()->removeListener(this);
}

void GameEngine::update()
{

	InputSystem::get()->update();

}

void GameEngine::onKeyPressed(int keyCode) 
{
	std::cout << char(keyCode) << " pressed" << std::endl;
}

void GameEngine::onKeyDown(int keyCode)
{
	//std::cout << char(keyCode) << " down" << std::endl;
}

void GameEngine::onKeyUp(int keyCode)
{
	//std::cout << char(keyCode) << " up" << std::endl;
}
