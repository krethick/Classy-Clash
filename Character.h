
/*
  We created our own header file

  const int maxFrames{6};             // Because of 6 images in the sprite
  const float updateTime{1.f / 12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.
  const float speed{4.f};

  We need to remove const from these variables because const variables in a class prevent some more advanced things such as 
  copy assignment and move semantics.
*/

// Under the header file declare the class and it's variables
#include "raylib.h"
// Create a class character
class Character
{
public:  // Section public                                    
  Character();  // Constructor (Function name)
  Vector2 getWorldPos() { return worldPos; } // In a more compact form (This is a getter)
  void setScreenPos(int winWidth, int winHeight);
  void tick(float deltaTime);

private: // Section Private
  Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
  Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
  Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
  Vector2 screenPos{}; // Screen position (Note: Make sure {} its initialised with 0 values, to prevent garbage data)
  Vector2 worldPos{};  // World Position
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
};