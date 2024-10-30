#include "Core/Game.h"
#include "../Testing/TestScene.h"

int main()
{
    Game game(1280, 720);

    TestScene testScene;
    game.AddScene("testScene", &testScene);

    game.Run();

    return 0;
}