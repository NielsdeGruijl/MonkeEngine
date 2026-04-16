cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES
CPP_Framework/Framework/Main.cpp
CPP_Framework/Framework/Collisions/AABBCollider.cpp
CPP_Framework/Framework/Collisions/BruteForce.cpp
CPP_Framework/Framework/Collisions/CoarseProximityTest.cpp
CPP_Framework/Framework/Collisions/CollisionChecker.cpp
CPP_Framework/Framework/Collisions/CollisionPair.cpp
CPP_Framework/Framework/Collisions/EdgePoint.cpp
CPP_Framework/Framework/Collisions/SpatialGrid.cpp
CPP_Framework/Framework/Collisions/SpatialNode.cpp
CPP_Framework/Framework/Collisions/SweepAndPrune.cpp
CPP_Framework/Framework/Collisions/TwoDimensionalSAP.cpp
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
CPP_Framework/Testing/CollisionTestScene.cpp
CPP_Framework/Testing/Enemy.cpp
CPP_Framework/Testing/LeftObject.cpp
CPP_Framework/Testing/PerformanceTestScene.cpp
CPP_Framework/Testing/Player.cpp
        CPP_Framework/Framework/Math/Time.h
        CPP_Framework/Testing/ShootingCollisionScene.cpp
        CPP_Framework/Testing/ShootingCollisionScene.h
        CPP_Framework/Testing/Projectile.cpp
        CPP_Framework/Testing/Projectile.h)

add_executable(MyProject ${SOURCES})

target_link_libraries(MyProject sfml-graphics sfml-window sfml-system)
