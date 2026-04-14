#include "Core/Game.h"
#include "../Testing/CollisionTestScene.h"
#include "../Testing/PerformanceTestScene.h"

int main()
{
    Game game(2560, 1440);
    
    CollisionTestScene testScene;

    PerformanceTestScene pTestScene;
    game.AddScene("asteroidsScene", &testScene);

    game.Run();

    return 0;
}