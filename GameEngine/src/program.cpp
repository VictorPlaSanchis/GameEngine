#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GameEngine.h"
#include "Log/Log.h"

int main(int argc, char* argv[])
{
    // Initializing core log
    vge::Log::get()->Init();

    // Initializing Game Engine singleton and running it
    vge::GameEngine::get()->Init();
    vge::GameEngine::get()->Run();

    return 0;
}