/*
  Prop Collison:
    * In order to check collison with the prop we need the prop's screen position.
    * That is going to involve x and y of the screenPos
    * We are going to need the rock's width and height ,which is going to involve that scale varaiable
      as we're drawing the rock at a scale that's different than the size of the texture itself.
    
    
*/

#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
#include "Character.h" // Call the character.h header file
#include "Prop.h" // Call the prop.h header file

int main()
{
  int windowDimensions[2];
  windowDimensions[0] = 384; // Width
  windowDimensions[1] = 384; // Height
  
  
  // Initialise this window and use it before loop
  InitWindow(windowDimensions[0], windowDimensions[1], "Classy-Clash");

  Texture2D nature_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
  Vector2 mapPos{0.0, 0.0}; // This is for the map position
  const float mapScale{4.0f};
  
  
  Character knight{windowDimensions[0],windowDimensions[1]};



  Prop props[2]{  // Created the prop array and laoded the texture
      Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},  // Create an array of props, with the location keeping 600 and 300.
      Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}   // Create an array of props, with the location keeping 400 and 500.
  };       
 
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);
    
    // knight.getWorldPos() we created public getter for this.
    mapPos = Vector2Scale(knight.getWorldPos(), -1.f); // So now each frame we're getting the characters worldPos() vector and flipping it by muliplying it by -1 
                                                       // And this will move mapPos in the opposite direction.
                                                       // So the character will stay in the middle of the screen and the map will move.
   // Draw the map
    DrawTextureEx(nature_map, mapPos, 0.0, mapScale, WHITE); // We are drawing the map into the screen
    
    // Draw the props
    for(auto prop : props) // We'll be using range based for loop, we'll loop through the props array.
    {
       prop.Render(knight.getWorldPos()); // We'll be getting the position of the prop based on the knight's world position
    }

    knight.tick(GetFrameTime()); // The tick function handles movement

    // Check the map bounds
    if (knight.getWorldPos().x < 0.f ||
        knight.getWorldPos().y < 0.f ||
        knight.getWorldPos().x + windowDimensions[0] > nature_map.width * mapScale ||
        knight.getWorldPos().y + windowDimensions[1] > nature_map.height * mapScale
        ) // mapScale is nothing but scale 4
    {
       knight.undoMovement(); // Undo the movement
    }

    // Checking the prop collision
    for(auto prop:props)
    {
      if(CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
      {
        knight.undoMovement(); 
      }
      
    }
    EndDrawing();
  }
  UnloadTexture(nature_map);
  CloseWindow();
}