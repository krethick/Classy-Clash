// Import Character.h file and variables 
// Include all necessary logic here

/*
   screenPos = {(float)winWidth / 2.0f - 4.0f * (0.5f * width), 
               (float)winHeight / 2.0f - 4.0f * (0.5f * height)

    * We are taking the windowwidth (winWidth) and dividing by two and we're taking the window height and dividing by 2.0f
    * This gives us the center of the screen, but of course we have to move to the left and up by half of width and half of the height of our sprite.
    * Thats why we take half of the width and half of the height.(0.5f * width),(0.5f * height)
    * We are scaling that half by four (4.0f) because we're drawing the texture scaled by 4.
  
  C++ has a built in function called static cast, which checks the types at compile time and will prevent you from casting incompatible types.

  (float)winWidth This is a C style casting because it's a technique that came with the C programming language.
                  The C style cast can be dangerous as it doesn't check the types it's casting to or from.

  The C++ static cast function looks like this  static_cast<float>(winWidth)    <Give any data type you want>           
  };


*/

#include "Character.h"
#include "raymath.h"


Character::Character(int winWidth, int winHeight) // Initialise the Constructor
{
  width = texture.width/maxFrames;
  height = texture.height;

  screenPos = {static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width), 
               static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
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
  Rectangle destination{screenPos.x, screenPos.y, scale * width, scale * height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame; // Assign worldpos to worldPosLastFrame
}

Rectangle Character::GetCollisionRec()
{
  return Rectangle
  {
    screenPos.x,
    screenPos.y,
    width * scale,
    height * scale
  };
}