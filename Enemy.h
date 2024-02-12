#include "raylib.h"
class Enemy
{
    public:
      Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture); // Define a constructor
      Vector2 getWorldPos() { return worldPos; } // In a more compact form (This is a getter)
      void tick(float deltaTime);
      void undoMovement(); // Create an undo movement
      Rectangle GetCollisionRec(); // For collision 

    private:
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