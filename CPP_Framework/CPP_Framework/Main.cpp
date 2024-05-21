#include <SFML/Graphics.hpp>

//#include "Scene.h"
//#include "GameObject.h"
//#include "Sprite.h"
//#include "Player.h"
//#include "Enemy.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}