#include "GameEngine.h"
#include "Log/Log.h"

int main(int argc, char* argv[])
{
    vge::GameEngine::get()->Init();
    vge::GameEngine::get()->Run();
    return 0;
}