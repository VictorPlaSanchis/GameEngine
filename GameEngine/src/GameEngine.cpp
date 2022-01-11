#include "GameEngine.h"
#include "InputSystem/InputSystem.h"

GameEngine::GameEngine()
{
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

void GameEngine::onKeyDown(int keyCode)
{
}

void GameEngine::onKeyUp(int keyCode)
{
}
