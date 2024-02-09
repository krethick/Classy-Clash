/*
   Constructor Arguments
      
      Character.h
    
    class Character{
      public:
       Character(int winWidth, int winHeight); // Define the Constructor
       private:
        Vector2 screenPos{};
      }

      Character.cpp
    
    #include "Character.h"

    Character::Character(int winWidth, int winHeight) // Initiliase the constructor
    {
      screenPos = {(float)winWidth/2.f-4.f*(0.5f*width),
                   (float)winHeight/2.f-4.f*(0.5f*height)
      };
    }

    Prop Class :-
       We can have props to decorate our world. 
       It's going to have it's own:
        * Texture
        * World Position
        * Draw scale
      
      We are going to initialise the members using inputs in the constructor

      Prop.h
        * Will have a Texture
        * Will have a World Position
        * Will have a float called scale
      
      class Prop
      {
        public:
          Prop();
        private:
          Texture2D texture{}; // Will have a Texture
          Vector2 worldPos{}; // Will have a World Position
          float scale; // Will have a float called scale
      }
   
   Ending as we move, the rock moves along the map

   Refer the pdf file
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

  Prop rock{Vector2{0.0,0.0}, LoadTexture("nature_tileset/Rock.png")}; // Load the Rock texture

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

    rock.Render(knight.getWorldPos());

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
    EndDrawing();
  }
  UnloadTexture(nature_map);
  CloseWindow();
}