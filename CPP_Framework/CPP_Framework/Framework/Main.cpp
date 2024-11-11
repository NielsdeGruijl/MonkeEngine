#include "Core/Game.h"
#include "../Testing/TestScene.h"
#include "../Testing/CollisionTestScene.h"

int main()
{
    Game game(1280, 720);

    TestScene testScene;
    //game.AddScene("testScene", &testScene);

    CollisionTestScene collisionTestScene;
    game.AddScene("CollisionTestScene", &collisionTestScene);

    game.Run();

    return 0;
}