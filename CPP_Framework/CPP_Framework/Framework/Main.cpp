#include "Core/Game.h"
#include "../Testing/CollisionTestScene.h"
#include "../Testing/PerformanceTestScene.h"

int main()
{
    Game game(1280, 720);
    
    CollisionTestScene testScene;

    PerformanceTestScene pTestScene;
    game.AddScene("asteroidsScene", &pTestScene);

    game.Run();

    return 0;
}