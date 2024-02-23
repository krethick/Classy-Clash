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

  => Variable Addresses (Pointers) :-
       * When we run a program, the variables and functions take up space in physical memory.
       * All of our variables require some memory in the hardware.
       * That memory exists in a particular location, and each memory location has its own address.
    
    Explanation
      float damage (10.f) this float variable exists somewhere on the => Memory.
       * We can get the memory address of this variable with the address of operator (&) and it looks like this &damage.
       * The address of operator returns the address of the variable.
       
       The damage(float) is  type float => we store the address of a variable in a pointer float* ptr i.e float* ptr = &damage
        * We refer to this type as pointer or pointer to float or sometimes float star.(float* ptr)

     For eg:
      float damage{10.f};
      float* ptr = &damage;

      float howMuch = *ptr; This returns the actual variable that the pointer is pointing to.  (*ptr is dereference operator)
      (So we use the dereference operator to access the variable pointed to by a pointer)

    => Arrow Operator:
        i) goblin.target = &knight; // Initialise the memeber variable with the address of a character instance
        (Say we have knight and we get its address with the address operator and use the assignment
        operator to assign that address to that target variable.)
        ii) goblin.target
        (Now accessing the pointer through the goblin class with the DOT operator will simply yield the address to the knight)
        
        To access the knight character we need to use the dereference operator like this:
         iii) *goblin.target

        But what if we like to call a function on that character?
          iv) (*goblin.target).getWorldPos()

        But these things are complex

        There is a special operator that is a shortcut to doing this.
         => It's called the arrow operator.(->)
             goblin.target->getWorldPos()
            (Using the arrow operator on a pointer allows us to access members and methods on the pointer to object)

    Enemy Screen Position :-
       * As the character moves around throughout the map, the enemy stays in the upper left corner of the screen.
       * This is because the enemies screen pos variable has been declared and initialized using braced initialisation{}
         So it has a vector2 value of 0,0 and we never actually updating that value.

    Enemy AI: 
      We need to create an logic where the enemy chases the character.
       * Refer from the Enemy AI notes.
       
       * Pseudocode:
            It helps us to write out a roadmap of where we want to go in our code.

               in Enemy::tick();
            Get toTarget
            Normalize toTarget
            Multiply |toTarget| by speed
            Move Enemy
       
     Enemy Run Animation:
         The enemy sprite sheet is going to have two states.
           * Idle 
           * Run 
      
      Drawing the sword:
       * We are going to use Weapon Texture
       * DrawTexturePro()
       
       -> DrawTexturePro() takes a Vector2 called Origin and it behaves as the origin for the texture that we're drawing. 
       -> If we choose origin = {0.f, 0.f}, that is going to be the upper left corner of the texture.
       -> Instead if we choose the lower left corner of the texture as the origin, that's going to be 0 for the X and height for the y. Origin = {0.f, height}

       Implementing Attack Functionality:
          * alive bool - We will be adding a Boolean called Alive so we can know if a character or an enemy is alive or dead
          * Swing the sword - We will swing the sword by changing its rotation 
          * Weapon Collision: We are going to implement this so we can know if we'e hit an enemy with the sword
          
      Health and Damage:
         * We'll be having a health variable
         * Enemy damaging the Character
      
      Strings and Displaying Health
         * Display health on the screen
         * C-style strings
         * The std::string type
      
      Refer to the string.pdf notes

      Multiple Enemies:
         * Enemy Chase Radius
         * More enemies
         * Store enemies in a array
      
       Why  we need chase radius?
           The enemey starts to glitch out when it gets close because it's reaching its destination and continuing to
           move as that two target vector is no longer meaningful when the enemy reaches the character.


*/

#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
#include "Character.h" // Call the character.h header file
#include "Prop.h" // Call the prop.h header file
#include "Enemy.h" // Call the Enemy class
#include <string> // We can use the standard string

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
     Vector2{800.f, 300.f},
     LoadTexture("characters/goblin_idle_spritesheet.png"),
     LoadTexture("characters/goblin_run_spritesheet.png")
  };

  Enemy slime{
    Vector2{500.f, 700.f},
    LoadTexture("characters/slime_idle_spritesheet.png"),
    LoadTexture("characters/slime_run_spritesheet.png")
  };

  Enemy* enemies[]{
     &goblin,
     &slime
  };

  for (auto enemy : enemies)
  {
    enemy->setTarget(&knight);
  }

   goblin.setTarget(&knight);  // get the settarget() using the address of the knight character
 
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

    if (!knight.getAlive()) // Character is not alive
    {
       DrawText("Game Over!", 55.f, 45.f, 40, RED);
       EndDrawing();
       continue; // If you use a continue keyword inside a loop. Once the flow of execution reaches the continue, the rest of the loop body is 
                 // ignored and the next iteration of the loop will start.
    }
    else // Character is alive
    {
       std::string knightsHealth = "Health: "; // Initiliase a string variable
       knightsHealth.append(std::to_string(knight.get_health()), 0, 5); // Append the string
       DrawText(knightsHealth.c_str(), 55.f, 45.f, 40,RED); // Draw the text
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
    
    for (auto enemy : enemies)
    {
       enemy->tick(GetFrameTime());
    }

    // Check for weapon and enemey collision
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //By default it's true but we can also mention it true as well (optional)
    {
      for (auto enemy : enemies)
      {
        if(CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec())) // By default it's true but we can also mention it true as well (optional)
        {
           enemy->setAlive(false);
        }
        // To format the document clcik shift + alt + f
      }
    }
    

    EndDrawing();
  }
  UnloadTexture(nature_map);
  CloseWindow();
}