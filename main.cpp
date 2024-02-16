/*
  Prop Collison:
    * In order to check collison with the prop we need the prop's screen position.
    * That is going to involve x and y of the screenPos
    * We are going to need the rock's width and height ,which is going to involve that scale varaiable
      as we're drawing the rock at a scale that's different than the size of the texture itself.
    
  Enemy Class:
     * Needs Textures for idle and run animation
     * its going to need a position i.e Vector2
       -> World, Screen
     * Tick
        -> Update the Animation and Draw the Texture
     * Undo Movement 
        -> We need an undo movement function so we can undo movement
           in the case where the enemy is bumping up against props and needs to be
           prevented from moving
     * Collision Rec
         We are going to need a collison rectangle so we'll know if its colliding
         with props or the character.

  Class Inheritance:
        * Inheritance is a feature or a process in which, new classes are created from the exisiting classes.  
        * The new class are created from the exisiting classes.
        * The exisiting class is known as the base class or parent class.
        * The derived class now is said to be inherited from the base class.
  
  We are going to create a base character class so the character class and the enemy class can both be based on this parent
  class base character.

  Base Character class:
      * Character
      * Enemy
  
  Eg: Class Inheritance

  class Parent                                   * The Parent has a public constructor
  {                                              
     public:
     Parent();                                   * Public Function
     Vector2 getWorldPos();
    private:                                     * Private Varibale
     Vector2 worldPos{};
  }

  Class Child : Parent                            * Child is inheriting (:) from the parent or deriving from the parent
  {              Vector2 worldPos{};              * Parent is the base class
  }       Vector2 getWorldPos();  are inherited   * Child is derived from the parent or is the child class of parent

 * When a class derives from another class, it inherits members and methods from the base class.
 * We say the instance of the child class is parent, since it inherits the members and methods of parent, we can say
   that it is actually a parent
 * A parent is not a child i.e it does not have members and methods that are decalared in the child class

 class Child : public Parent
 {
    // We can place access modifiers just before the base class name when inherititng from classes and public is the most 
       common access modifiers that you'll see here
    // By default if we don't mention the keyword it becomes private.
    // 
 }
   
   Let's say we have an instance of the child class.
   Child kid{};

   Vector2 kidPos = kid.worldPos; // We'll get an error because world pos is inaccessible because it's private and can only be accessed from within the parent class.
   Vector2 kidPos = kid.getWorldPos(); // We won't get any errors because this is a public method and it's accessible.
    
   There exists another access modifier keyword and that's protected.

   * Members and methods in a protected section are accessible from within the class that they're derived in
     and also from within classes that derive from this class.

    
   class Parent
   {
      public:
        Parent();
        Vector2 getWorldPos();
      protected:
        Vector2 worldPos{};
   }

   class Child : public Parent
   {

   }

   Child kid{};

   Vector2 kidPos = kid.worldPos; //  If WorldPos were a protected member, then accessing worldPos from a child instance is valid and the member is accessible
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