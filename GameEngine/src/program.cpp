#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GameEngine.h"
#include "Debug/Instrumentor.h"

// TODO
//
//  Roating system on Transform class
//  Chesk SpriteRenderer class functionalities
//  Start making magic!
//
//

int main(int argc, char* argv[])
{
    PROFILE_BEGIN_SESSION("GAME_ENGINE_PROFILE", "first_profile.json");

    GameEngineVGE.Init();
    GameEngineVGE.Run();

    PROFILE_END_SESSION();

    return 0;
}