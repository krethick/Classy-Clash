#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) 
{ // ThE Enemy class inherits these variables from the base character.h (note check the Enemy.h)
  worldPos = pos;
  texture = idle_texture;
  idle = idle_texture;
  run = run_texture;
   
  width = texture.width/maxFrames;
  height = texture.height;
  speed = 3.5f;
}


void Enemy::tick(float deltaTime) // Child class deriving from BaseCharacter (Parent class)
{
  // Enemy AI

   // get toTarget
   Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);// (Because we are not on the character itself, we can only access public members and methods since 
                                                                        // we're attempting to access them from outside of the character class.)
                                                                       // This means that in order to get screenPos, we need a public getter(go to the character class). 
   // Normalize to Target
   toTarget = Vector2Normalize(toTarget); // Vector2Normalize does not actually change the variable to target, it simply uses it in its calculation and then return the result as Vector2.
                                          // toTarget value gets overwritten.   
   // Multiply toTarget by speed
   toTarget = Vector2Scale(toTarget, speed); // Results in a length of speed

   // Move Enemy (set worldPos) towards the character
   worldPos = Vector2Add(worldPos, toTarget);
   screenPos = Vector2Subtract(worldPos, target->getWorldPos()); // World position - Enemey pointer pointing to Knight(Character's) world position
                                                                 // When the knight moves forward goblin goes backward and stays put.
  
   BaseCharacter::tick(deltaTime); // Call the basecharacter functionality in the Enemy class
}



