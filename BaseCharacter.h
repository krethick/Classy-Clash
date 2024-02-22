/*
  How do we get around especially the errors including same header file twice ? 
   => Conditional Compilation:

   Inheriting from the Base Character
         
*/

// This preprocessor directive checks whether a specific identifier/header file is defined or not
// If the identifier is not defined, the code within the #ifndef block is processed. 
// If the identifier is defined, the code within the #ifndef block is skipped.

#ifndef BASE_CHARACTER_H  // if not defined, the header checks if BASE_CHARACTER_H exists (Yes it don't exist)
                          // if already exists the line of code does'nt execute.
                         
#define BASE_CHARACTER_H // If true define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter  // Create the base the BaseCharacter
{
    public:
       BaseCharacter();
       Vector2 getWorldPos() { return worldPos; } // In a more compact form (This is a getter)
       void undoMovement(); // Create an undo movement
       Rectangle GetCollisionRec(); // For collision 
       virtual void tick(float deltaTime);
       virtual Vector2 getScreenPos() = 0;

        /* virtual Vector2 getScreePos() = 0;
           Since this is going to be overridden 
           Since this is going to be overridden in character and enemy it needs to be virtual.
           If we want to decalre it here and don't want to define it, Pure virtual functions are marked with 0
           Once we have a pure virtual function on the base character class, the base character class is now said to be an abstract class, which means we cannot create an instance 
           from it but we can only derive child classes from it. */

       
    protected: // We make a protected section because the child classes can access those variables.
      Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
      Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
      Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
      Vector2 screenPos{}; // Screen position (Note: Make sure {} its initialised with 0 values, to prevent garbage data)
      Vector2 worldPos{};  // World Position
      Vector2 worldPosLastFrame{}; // World Pos last frame
      // 1 : Facing right and -1 : Facing Left
      float rightLeft{1.f};
      // Animation Variables for the character
      float runningTime{};
      int frame{};
      int maxFrames{6};             // Because of 6 images in the sprite
      float updateTime{1.f / 12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.
      float speed{4.f};
      float width{};
      float height {};
      float scale{4.0f};
      Vector2 velocity{}; // This vector contains information regarding the direction of movement as well as the distance we should move this particular frame.

    private:
};


#endif // Exit.