// Import Character.h file and variables 
// Include all necessary logic here

#include "Character.h"
#include "raymath.h"


Character::Character() // Initialise the Constructor
{
  width = texture.width/maxFrames;
  height = texture.height;
}
// Under Character class we have setScreenPos
void Character::setScreenPos(int winWidth, int winHeight) // Define it and We paste the function prototype only.
{
  screenPos = {
      (float)winWidth / 2.0f - 4.0f * (0.5f * width), //(0.5 * knight.width/6.0) we are subtracting half of the knight's width
      (float)winHeight / 2.0f - 4.0f * (0.5f * height)       // (0.5 * knight.height) we are subtracting half of the knight's height
  };
}

// Under Character class we have tick
void Character::tick(float deltaTime)
{
  worldPosLastFrame = worldPos; // Assign worldpos to worldPosLastFrame

  Vector2 direction{}; // Vector For the camera movement
  if (IsKeyDown(KEY_A))
    direction.x -= 1.0; // Moves to the left so negative
  if (IsKeyDown(KEY_D))
    direction.x += 1.0; // Moves to the right so positive
  if (IsKeyDown(KEY_W))
    direction.y -= 1.0; // Moves upwards thats why negative
  if (IsKeyDown(KEY_S))
    direction.y += 1.0; // Moves downwards thats why positive
  if (Vector2Length(direction) != 0.0)
  {
    // Set worldPos = worldPos + direction Vector2Normalize(direction)
    // Instead subtracting direction we are adding direction because we're changing the character's world position.
    worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed)); // Vector2Normalize(direction) It is normalised and had a length of 1

    // Ternary operator (This operator works on three arguments only in C++)
    direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    texture = run; // Knight character runs
  }
  else
  {
    texture = idle; // Knight character goes to idle.
  }

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
  Rectangle destination{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame; // Assign worldpos to worldPosLastFrame
}