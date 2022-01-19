#include "SourceScript.h"
#include "InputSystem/InputSystem.h"
#include "Log.h"

SourceScript::SourceScript()
{
}

SourceScript::~SourceScript()
{
}

void SourceScript::Update()
{

	if (InputSystem::get()->isKeyPressed('A')) {
		Log::debug(Log::getLogAuxiliar(), "Executing Source Code behaviour... [MOVING LEFT]", spdlog::level::info);
	}

	if (InputSystem::get()->isKeyPressed('S')) {
		Log::debug(Log::getLogAuxiliar(), "Executing Source Code behaviour... [MOVING DOWN]", spdlog::level::info);
	}	

	if (InputSystem::get()->isKeyPressed('D')) {
		Log::debug(Log::getLogAuxiliar(), "Executing Source Code behaviour... [MOVING RIGHT]", spdlog::level::info);
	}

	if (InputSystem::get()->isKeyPressed('W')) {
		Log::debug(Log::getLogAuxiliar(), "Executing Source Code behaviour... [MOVING UP]", spdlog::level::info);
	}	

}