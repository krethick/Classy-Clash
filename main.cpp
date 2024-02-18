/*
  What is function Overriding?
    => Function overloading is a feature of object-oriented programming where two or more functions can have 
   the same name but different parameters. 
  
  Example of Overriding Function:

  class Parent
  {
    public:
      virtual void tick(float deltaTime)
      {
         // include parent properties.
      }
  }

  class Child : public Parent
  {
    virtual void tick(float deltaTime) override
    {
      // Include child properties
    }
  }

  HOW OVERRIDE WORKS?
   => Parent dad{}; // This is an instance of the parent class
      dad.tick(GetFrameTime()); // If we call the tick function from the instance then the code that runs will 
                                   be that code in the parent version.
      
  =>  Child kid{}; //If we have an instance of the child class
      kid.tick(GetFrameTime()); If we call this function, we get the override version which may have it's own unique code.

   What happens if you have an override in a child class and you want
   to execute your own unique code and also want to execute the code in the parent function?

   => We can do it by calling the parent version of the function and fully qualify the function
      name with the base class name.
      ( * Call Parent version, 
        * Fully qualify with base class name
        * Pass in required parameters)
      
      class Child : public Parent 
      {
        virtual void tick(float deltaTime) override
        {
          // Implement child functionalities

          // Implement parent functionalities
          Parent::tick(deltaTime); => Pass in required parameters
        }
      }
       



  What is Virtual Function?
  => Virtual section is member function that is declared within a base class and is re-defined by a derived 
     class.
  
  What is Override identifier?
  => But there may be situations when a programmer makes a mistake while overriding that function. 
     So, to keep track of such an error, C++11 has come up with the override identifier. 
     If the compiler comes across this identifier, it understands that this is an overridden version of the same class.

*/

#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
#include "Character.h" // Call the character.h header file
#include "Prop.h" // Call the prop.h header file
#include "Enemy.h" // Call the Enemy class


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

  Enemy goblin{
     Vector2(),
     LoadTexture("characters/goblin_idle_spritesheet.png"),
     LoadTexture("characters/goblin_run_spritesheet.png")
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
    
    goblin.tick(GetFrameTime());

    EndDrawing();
  }
  UnloadTexture(nature_map);
  CloseWindow();
}