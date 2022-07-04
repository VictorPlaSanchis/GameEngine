#ifdef _WIN32
#include <Windows.h>	// avoid compilation redefinition of APIENTRY
#endif
#include "GameEngine.h"
#include "Debug/Instrumentor.h"
#include "./Types/Vector.h"
#include "./Types/Quaternion.h"

// TODO
//
//  Roating system on Transform class
//  Chesk SpriteRenderer class functionalities
//  Start making magic!
//
//

int main(int argc, char* argv[])
{

    vge::Quaternion<float> A = vge::Quaternion<float>(3.0f, Vector3F({1.0f, 2.0f, 3.0f}));
    vge::Quaternion<float> B = vge::Quaternion<float>(1.0f, Vector3F({ 3.0f, 2.0f, 1.0f }));
    vge::Quaternion<float> C = A * B;

    PROFILE_BEGIN_SESSION("GAME_ENGINE_PROFILE", "first_profile.json");

    GameEngineVGE.Init();
    GameEngineVGE.Run();

    PROFILE_END_SESSION();

    return 0;
}