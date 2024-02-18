
/*
  We created our own header file

  const int maxFrames{6};             // Because of 6 images in the sprite
  const float updateTime{1.f / 12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.
  const float speed{4.f};

  We need to remove const from these variables because const variables in a class prevent some more advanced things such as 
  copy assignment and move semantics.

  Start at 2:15
*/

// Under the header file declare the class and it's variables
#include "raylib.h"
#include "BaseCharacter.h"
// Create a class character
class Character : public BaseCharacter // Character functionalities derived from the BaseCharacter class
{
public:  // Section public                                    
  Character(int winWidth, int winHeight);  // Constructor (Function name)
  Vector2 getWorldPos() { return worldPos; } // In a more compact form (This is a getter)
  virtual void tick(float deltaTime) override; // two or more functions can have the same name but different parameters. 
 
 private: // Section Private
  
  
};