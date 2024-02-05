/*
  Scope:
    * Statement scope (if,else,while, etc)
    * Function scope
    * Class scope 
    * Global scope
    
   Statement Scope :-

   if (numEnemies > 0 )
   {
     float damage = getAttackDmg();
     dealDamage(damage);
   }

   damage = 0.f; => As per the compiler it has done out of scope

   Function Scope :-
      If we declare a variable inside of a function, that varaiable does not exist outside of the function

   bool alive (float dmg, float health)
   {
     float remaining  = health - dmg ;
     return remaining > 0.f;
   }

   remaining = 0.f; => This gives us an error because it is a local variable

   Note: A function input parameters are also local to the function, so attempting to use them outside of the
         function would also be an error.

  dmg = 0.f; => Out of scope
  Health = 0.f; => Out of scope

  Class Scope :
     class Barabarian
     {
       public:
         void setDamage(float amount)   // We can have functions that can access and change the varaiables that belong to the class.
         {                              // That's because class methods or member functions have access to variables in the class.
           if(amount > 0.f)
           {
             dmamage = amount;
           }
         }
        private:                      // Private means inaccessible outside of the class, but class functions are inside the class.
           float damage;
     };

     The member variable (float damage;) has class scope, meaning it only exists inside of the class and to attempt to use this
     variable outside of the class would be an error.

     Note: There is a difference between a class and an instance of that class
              
           Class : It is more like the schematics (showing the important features but not the details) required to create a variable of that class.
           Instance of a class : It is an actual object that exists in the code.

        Eg: Barbarian conan;
            conan.setDamage(20.f);
                                          We have two seperate barbarian instances, each with thier own unique value sored in thier damage variable.
            Barbarian xena;
            xena.setDamage(60.f);

            conan => damage = 20.f
            xena => damage = 60.f

    Global Scope :
       
       float damage{6.f}; // This varaiable has global scope and we can use it anywhere in the program 

       int main()
       {
         float health = 10.f;
         float remaining = health - damage; => So this float variable damage was decalred outside the main function
                                               So using it in the main function is valid since the variables has global scope
       }

       * We decalre a global variable outside of all functions and outside of all classes.
       * Exists everywhere in the program and will survive until the end of the program.

*/ 


#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs

// Create a class character
class Character{
  public: // Section public
    Vector2 getWorldPos()  {return worldPos;} // In a more compact form (This is a getter)

  private: // Section Private
      Texture2D texture;
      Texture2D idle;
      Texture2D run;
      Vector2 screenPos; // Screen position
      Vector2 worldPos; // World Position
      // 1 : Facing right and -1 : Facing Left 
      float rightLeft{1.f};
      // Animation Variables for the character
      float runningTime{};
      int frame{};
      const int maxFrames{6}; // Because of 6 images in the sprite
      const float updateTime{1.f/12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.
 };

int main()
{
    int windowDimensions[2];
    windowDimensions [0] = 384; // Width
    windowDimensions [1] = 384; // Height

    // Initialise this window and use it before loop
    InitWindow(windowDimensions[0],windowDimensions[1], "Classy-Clash");

    Texture2D nature_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0}; // This is for the map position 
    float speed {4.0};
    
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos {
        // We use 4.0 for scaling the Knight height and width
        // (float)(0.5f * knight.width/6.0f) float is used for type casting
        (float)windowDimensions[0]/2.0f - 4.0f * (float)(0.5f * knight.width/6.0f), //(0.5 * knight.width/6.0) we are subtracting half of the knight's width
        (float)windowDimensions[1]/2.0f - 4.0f * (float)(0.5f * knight.height)    // (0.5 * knight.height) we are subtracting half of the knight's height
    };

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png"); // Knight character idle Texture

    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png"); // Knight character running Texture

    
    // 1 : Facing right and -1 : Facing Left 
    float rightLeft{1.f};

    // Animation Variables for the character
    float runningTime{};
    int frame{};
    const int maxFrames{6}; // Because of 6 images in the sprite
    const float updateTime{1.f/12.f}; // We use 1.f/12.f, so our animation will update 12 times per second.

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        Vector2 direction{}; // Vector For the camera movement
        if(IsKeyDown(KEY_A)) direction.x -= 1.0; // Moves to the left so negative
        if(IsKeyDown(KEY_D)) direction.x += 1.0; // Moves to the right so positive
        if(IsKeyDown(KEY_W)) direction.y -= 1.0; // Moves upwards thats why negative
        if(IsKeyDown(KEY_S)) direction.y += 1.0; // Moves downwards thats why positive 
        if (Vector2Length(direction) != 0.0)
        {
           // Set mapPos = mapPos - direction Vector2Normalize(direction)
          mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed)); // Vector2Normalize(direction) It is normalised and had a length of 1
           
           // Ternary operator (This operator works on three arguments only in C++)
           direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
           knight = knight_run; // Knight character runs
       } 
       else
       {
          knight = knight_idle; // Knight character goes to idle.
       }
        
        // Draw the map
        DrawTextureEx(nature_map, mapPos, 0.0, 4.0, WHITE); // We are drawing the map into the screen

        // Update animation frame
        // Note we can use a delta time or the GetFrameTime (Both are same)
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
           frame++;
           runningTime = 0.f;
           if(frame > maxFrames) frame = 0;
        }


         // Draw the knight character
        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height}; // We use 0.f for x and y
        Rectangle destination {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height}; // We use 4.0 to scale the knight image size
        Vector2 origin{};
        DrawTexturePro(knight,source,destination,origin,0.f,WHITE);
        EndDrawing();
    }
    UnloadTexture(nature_map);
    CloseWindow();
}