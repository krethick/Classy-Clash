#include "raylib.h" // Incase if you want to include Texture2D

class Prop
{
  public:
     // We'll be declaring a constructor
     Prop(Vector2 pos, Texture2D tex);
     void Render(Vector2 knightPos); // For Rendering
  private:
    // Here we'll be having private variables
    Texture2D texture{};
     Vector2 worldPos{};
    float scale{4.f};
};