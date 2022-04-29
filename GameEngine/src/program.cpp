#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GameEngine.h"
#include "Types/Vector.h"

#include "Instrumentor.h"

int main(int argc, char* argv[])
{
    PROFILE_BEGIN_SESSION("GAME_ENGINE_PROFILE", "first_profile.json");

    // Initializing Game Engine singleton and running it
    vge::GameEngine::get()->Init();
    vge::GameEngine::get()->Run();

    PROFILE_END_SESSION();

    return 0;
}