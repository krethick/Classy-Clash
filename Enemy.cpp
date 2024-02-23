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
 

  if(!getAlive()) return; // if the enemy not alive
  
  // Enemy AI
  
  // get toTarget
   velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());// (Because we are not on the character itself, we can only access public members and methods since 
                                                                        // we're attempting to access them from outside of the character class.)
                                                                        // This means that in order to get screenPos, we need a public getter(go to the character class). 
   // Get toTarget

   if(Vector2Length(velocity) < radius) velocity = {}; // Radius functionality is implemented
   /*
     As Normalizing vector, scaling it by speed and adding it to world
     pos is already done in tick() we remove those lines of code.
   */   
  BaseCharacter::tick(deltaTime); // Call the basecharacter functionality in the Enemy class

   // Reducing health for the enemy
  if(CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
  {
    target->takeDamage(damagePerSec * deltaTime);
  }
}

Vector2 Enemy :: getScreenPos()
{
  
  // Move Enemy (set worldPos) towards the character
  return Vector2Subtract(worldPos, target->getWorldPos()); // World position - Enemey pointer pointing to Knight(Character's) world position
                                                          // When the knight moves forward goblin goes backward and stays put.
}



