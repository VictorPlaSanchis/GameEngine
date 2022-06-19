#include "MyGameScript.h"
#include "../Log/Console.h"
#include "../InputSystem/InputSystem.h"

namespace vge {

	MyGameScript::MyGameScript()
	{
	}

	MyGameScript::~MyGameScript()
	{
	}

	void MyGameScript::Behaviour()
	{
		if (InputSystem::get()->isKeyPressed(65)) {
			Console::debug("Im alive...", Console::COLOR::CYAN, Console::SENDER::AUXILIAR);
		}

	}

}