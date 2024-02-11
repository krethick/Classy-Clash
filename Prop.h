#include "raylib.h" // Incase if you want to include Texture2D

class Prop
{
  public:
     // We'll be declaring a constructor
     Prop(Vector2 pos, Texture2D tex);
     void Render(Vector2 knightPos); // For Rendering
     Rectangle GetCollisionRec(Vector2 knightPos); // Since this involves screen position, it's going to require the knight position, as the screen 
                                                   // position of a peop depends on the knight position.
    
  private:
    // Here we'll be having private variables
    Texture2D texture{};
     Vector2 worldPos{};
    float scale{4.f};
};