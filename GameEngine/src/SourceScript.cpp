#include "SourceScript.h"
#include "InputSystem/InputSystem.h"
#include <iostream>

SourceScript::SourceScript()
{
}

SourceScript::~SourceScript()
{
}

void SourceScript::beheaviour()
{
	if (InputSystem::get()->isKeyPressed('A')) {
		std::cout << "HELLO WORLD!" << std::endl;
	}
}