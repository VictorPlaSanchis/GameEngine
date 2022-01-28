#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GameEngine.h"

#include "Types/Vector.h"

int main(int argc, char* argv[])
{

    // Initializing Game Engine singleton and running it
    vge::GameEngine::get()->Init();
    vge::GameEngine::get()->Run();

    return 0;
}