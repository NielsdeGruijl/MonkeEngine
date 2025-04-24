#include "Core/Game.h"
#include "../Asteroids/AsteroidsScene.h"

int main()
{
    Game game(1280, 720);
    
    AsteroidsScene asteroidsScene;
    game.AddScene("asteroidsScene", &asteroidsScene);

    game.Run();

    return 0;
}