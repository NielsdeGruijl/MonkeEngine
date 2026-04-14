# [WIP] MonkeEngine
MonkeEngine is a 2D physics engine developed using C++, and SFML 2.5.1 for rendering. 
This engine is being developed as a learning experience, but the dream is to someday develop a (small) game with it!


# Physics
The engine has a robust collision system, being able to solve for rigidibody vs static object and rigidbody vs rigidbody collisions.
Rigid bodies are physics components that enable physics like velocity, drag, mass, friction and collisions on game objects.

Dynamic rigid body through player input (blue) versus rigid body receiving no input (red).
![](https://github.com/NielsdeGruijl/MonkeEngine/blob/main/ReadMeAssets/Untitled%20Project.gif)

Sweep and prune demo showing hundreds of objects moving and colliding at the same time.
![](https://github.com/NielsdeGruijl/MonkeEngine/blob/main/ReadMeAssets/SAPShowcase.gif)
