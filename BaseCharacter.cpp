#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() // Use scope resolution operator to derive the constructor class from the "BaseCharacter.h"
{
    
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame; // Assign worldpos to worldPosLastFrame
}

Rectangle BaseCharacter::GetCollisionRec()
{
  return Rectangle
  {
    screenPos.x,
    screenPos.y,
    width * scale,
    height * scale
  };
}



// Under Character and enemy class we have tick
void BaseCharacter::tick(float deltaTime) // Parent class is having the values of basic functionalites for character and enemy
{
  worldPosLastFrame = worldPos; // Assign worldpos to worldPosLastFrame

  // Update animation frame
  // Note we can use a delta time or the GetFrameTime (Both are same)
  runningTime += deltaTime;
  if (runningTime >= updateTime)
  {
    frame++;
    runningTime = 0.f;
    if (frame > maxFrames)
      frame = 0;
  }

  // Draw the knight character (Click shift + alt + f to reform the document )
  Rectangle source{frame * width, 0.f, rightLeft * width, height}; // We use 0.f for x and y
  Rectangle destination{screenPos.x, screenPos.y, scale * width, scale * height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}