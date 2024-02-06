/*
   Header File and Constructors

   Header file for a class is created in the header file
   In the header file the class and its functions and variables are declared.
      
     Character.h
   class Character
   {
     public:

     void attack();
   }
    
   Then we create a source file for this class with the same name.
      
         Character.cpp

    #include "Character.h"
    void Character::attack()
    {
      // deal damage
      ....
    }


 What is a constructor ?
  => It is a function that has the same name as the class and it has no return type
  => A constructor gets called whenever you create or construct a new instance of a class type
  => Constructor gets called when an instance of the class gets created.
  => It's typically a place to enforce what's known as class and variants or things that should never change when it comes to a class
  
  Eg: class Character
      {
        public:
           Character(); // Constructor
           void attack();
      }


*/

#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
#include "Character.h" // Call the character.h header file

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