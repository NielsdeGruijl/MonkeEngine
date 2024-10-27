#include <SFML/Graphics.hpp>

#include "TestScene.h"
#include "GameObject.h"
#include "Pawn.h"

#include "Object.h"
#include "Time.h"

extern const int unitSize = 100;
Time _time;

int main()
{
    Scene* currentScene;
    TestScene testScene;


    currentScene = &testScene;

    Object* obj = testScene.FindObject("rectangle");

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    //window.setFramerateLimit(60);
    while (window.isOpen())
    {
        _time.CalculateDeltaTime();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        currentScene->RenderScene(&window);
        currentScene->UpdateScene();

        window.display();
    }

    return 0;
}