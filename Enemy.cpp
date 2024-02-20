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
}

void Enemy::tick(float deltaTime) // Child class deriving from BaseCharacter (Parent class)
{
   screenPos = Vector2Subtract(worldPos, target->getWorldPos()); // World position - Enemey pointer pointing to Knight(Character's) world position
  
   BaseCharacter::tick(deltaTime); // Call the basecharacter functionality in the Enemy class
}



