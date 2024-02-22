#include "BaseCharacter.h"
#include "raymath.h"

/*
  Base character is now an abstract class as it cannot be instantiated(to call a constructor of a Class which creates an an instance or object, of the type of that Class) 
  but only derived from.
*/

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
    getScreenPos().x,
    getScreenPos().y,
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

  // Let's update the movement
  if (Vector2Length(velocity) != 0.0)
  {
    // Set worldPos = worldPos + direction Vector2Normalize(direction)
    // Instead subtracting direction we are adding direction because we're changing the character's world position.
    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed)); // Vector2Normalize(direction) It is normalised and had a length of 1

    // Ternary operator (This operator works on three arguments only in C++)
    velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    texture = run; // Knight character runs
  }
  else
  {
    texture = idle; // Knight character goes to idle.
  }
  velocity = {}; // Once we update movement, we need to zero out the velocity 

  // Draw the knight character (Click shift + alt + f to reform the document )
  Rectangle source{frame * width, 0.f, rightLeft * width, height}; // We use 0.f for x and y
  Rectangle destination{getScreenPos().x, getScreenPos().y, scale * width, scale * height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}