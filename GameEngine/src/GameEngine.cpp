#include "GameEngine.h"
#include "InputSystem/InputSystem.h"

GameEngine::GameEngine()
{

	InputSystem::get()->addListener(this);
	std::cout << "Listener added..." << std::endl;

}

GameEngine::~GameEngine()
{
}

void GameEngine::Update()
{

	InputSystem::get()->update();

}

void GameEngine::onKeyDown(int keyCode)
{
	std::cout << keyCode << " [" << char(keyCode) << "] went down..." << std::endl;
}

void GameEngine::onKeyUp(int keyCode)
{
	std::cout << keyCode << " [" << char(keyCode) << "] went up..." << std::endl;
}
