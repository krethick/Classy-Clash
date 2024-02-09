
/*
 Prop 
*/

// Under the header file declare the class and it's variables
#include "raylib.h"
// Create a class character
class Character
{
public:  // Section public                                    
  Character(int winWidth, int winHeight);  // Constructor (Function name)
  Vector2 getWorldPos() { return worldPos; } // In a more compact form (This is a getter)
  
  void tick(float deltaTime);
  void undoMovement(); // Create an undo movement

private: // Section Private
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
  
};