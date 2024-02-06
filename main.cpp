/*
   Character instance:
    
    What's the difference between mapPos, screenPos and worldPos ?
     => Refer the pdf 
*/

#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs

// Create a class character
class Character
{
public:                                      // Section public
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
  const int maxFrames{6};             // Because of 6 images in the sprite
  const float updateTime{1.f / 12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.
  const float speed{4.f};
};

// Under Character class we have setScreenPos
void Character::setScreenPos(int winWidth, int winHeight) // Define it and We paste the function prototype only.
{
  screenPos = {
      (float)winWidth / 2.0f - 4.0f * (float)(0.5f * texture.width / 6.0f), //(0.5 * knight.width/6.0) we are subtracting half of the knight's width
      (float)winHeight / 2.0f - 4.0f * (float)(0.5f * texture.height)       // (0.5 * knight.height) we are subtracting half of the knight's height
  };
}

// Under Character class we have tick
void Character::tick(float deltaTime)
{
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
  Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * (float)texture.width / 6.f, (float)texture.height}; // We use 0.f for x and y
  Rectangle destination{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}

int main()
{
  int windowDimensions[2];
  windowDimensions[0] = 384; // Width
  windowDimensions[1] = 384; // Height

 
  // Initialise this window and use it before loop
  InitWindow(windowDimensions[0], windowDimensions[1], "Classy-Clash");

  Texture2D nature_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0}; // This is for the map position
  
  SetTargetFPS(60);
  Character knight;
  knight.setScreenPos(windowDimensions[0], windowDimensions[1]); // Height);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    
    // knight.getWorldPos() we created public getter for this.
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f); // So now each frame we're getting the characters worldPos() vector and flipping it by muliplying it by -1 
                                                       // And this will move mapPos in the opposite direction.
                                                       // So the character will stay in the middle of the screen and the map will move.
   // Draw the map
    DrawTextureEx(nature_map, mapPos, 0.0, 4.0, WHITE); // We are drawing the map into the screen
    knight.tick(GetFrameTime());
    EndDrawing();
  }
  UnloadTexture(nature_map);
  CloseWindow();
}