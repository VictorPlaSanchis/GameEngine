#include "GameEngine.h"
#include "Log/Log.h"

int main(int argc, char* argv[])
{
    GameEngine::get()->Init();
    GameEngine::get()->Run();
    return 0;
}