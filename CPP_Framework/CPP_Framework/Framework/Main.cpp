#include "Core/Game.h"
#include "../Testing/CollisionTestScene.h"
#include "../Testing/PerformanceTestScene.h"
#include "../Testing/ShootingCollisionScene.h"

int main()
{
    Game game(1920, 1080);
    
    //CollisionTestScene testScene;

    ShootingCollisionScene shootingScene;

    //PerformanceTestScene pTestScene;
    game.AddScene("asteroidsScene", &shootingScene);

    game.Run();

    return 0;
}

