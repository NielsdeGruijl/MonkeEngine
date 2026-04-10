cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(MyProject 
CPP_Framework/Framework/Main.cpp
CPP_Framework/Framework/Collisions/AABBCollider.cpp
CPP_Framework/Framework/Collisions/CollisionChecker.cpp
CPP_Framework/Framework/Components/Component.cpp
CPP_Framework/Framework/Components/RigidBody.cpp
CPP_Framework/Framework/Components/SpriteRenderer.cpp
CPP_Framework/Framework/Core/Game.cpp
CPP_Framework/Framework/Core/Scene.cpp
CPP_Framework/Framework/Core/SceneManager.cpp
CPP_Framework/Framework/Core/SceneRenderer.cpp
CPP_Framework/Framework/Input/InputActionMap.cpp
CPP_Framework/Framework/Input/InputHandler.cpp
CPP_Framework/Framework/Math/Vector2.cpp
CPP_Framework/Framework/Objects/GameObject.cpp
CPP_Framework/Asteroids/Asteroid.cpp
CPP_Framework/Asteroids/AsteroidSpawner.cpp
CPP_Framework/Asteroids/AsteroidsScene.cpp
CPP_Framework/Asteroids/Bullet.cpp
CPP_Framework/Asteroids/SpaceShip.cpp
CPP_Framework/Asteroids/Powerups/PowerupObject.cpp
CPP_Framework/Testing/CollisionTestScene.cpp
CPP_Framework/Testing/Player.cpp)

target_link_libraries(MyProject sfml-graphics sfml-window sfml-system)
