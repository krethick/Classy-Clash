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


Character::Character(int winWidth, int winHeight) : // Initialise the Constructor
    windowWidth(winWidth),
    windowHeight(winHeight)
{
  width = texture.width/maxFrames;
  height = texture.height;
}

Vector2 Character::getScreenPos()
{
   return Vector2{
    // This for the character only and the location is static.
     static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width), 
     static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
   };
}

// Under Character class we have tick
void Character::tick(float deltaTime) // Child class deriving from BaseCharacter (Parent class)
{
   if (IsKeyDown(KEY_A))
    velocity.x -= 1.0; // Moves to the left so negative
  if (IsKeyDown(KEY_D))
    velocity.x += 1.0; // Moves to the right so positive
  if (IsKeyDown(KEY_W))
    velocity.y -= 1.0; // Moves upwards thats why negative
  if (IsKeyDown(KEY_S))
    velocity.y += 1.0; // Moves downwards thats why positive
  BaseCharacter::tick(deltaTime); // We are using the velocity to update the world pos. So the base character tick function should be called after we update the
                                  // velocity. Since the base character now uses velocity and the zeros it out 
}

