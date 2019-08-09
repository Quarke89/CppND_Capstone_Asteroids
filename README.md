# CppND_Capstone_Asteroids

Asteroids game using SDL2 library

## Build instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Asteroids`.

## Code structure

### Game Object class

GameObject parent class hold position and texture of game object. Virtual functions for rendering object and updating object

**Derived classes**
GameObjectAsteroid: Used for creating asteroids. Update function is overriden to update asteroid position based on velocity

GameObjectShip: Used for creating the ship. Update function is overriden to update ship position based on user input, direction, and velocity

GameObjectLaser: Used for creating lasers when the ship shoots with user input. Update function used to update position based on velocity. Object is deleted once it goes off screen

GameObjectExplosion: Used for creating explosions left behind from asteroids. Update function cycles though sprite animations over time until expiration

GameObjectStatic: Used for displaying static objects like text and background image

### Menu class

**Derived classes**

