/*
   Getters and Setters:
      Acessor methods:
        * Getters:
            Designed to get private data from outside of a class.
      
      Mutator methods:
       * Setters:
            Designed to actually change the state or data of a class.

    Now, in general, The data stored in our member variable should be private.

    So what if we need to access that data ? 
        Getters provide access to data preventing us from being able to change it.
   
     class Barbarian
     {
      private:
        float damage;
     };

     Now we can define a function right here in the class.

     class Barbarian
     {
        public:
          float getDamage() // * Now we can add a function right here in the class. 
          {                    * This function called getDamage() simply returns the value of the private damage variable.
            return damage;     * We call this accessor method or simply getter for damage.
          }                    * This allows us to access damage but prevents us from being able to change damage (Data remains unchanged)
        
        private:
          float damage;
     };
    
    Mutator methods:
       * Allows us to actually change variables.
       * The advantage of having a function to change a class as memebers allows us to enforce rules dictating 
          the way we change the state of the class (Rules can be enforced).

    class Barbarian
    {
     public:
       void setDamage(float amount) => Mutator emthod
       {
         if(amount > 0.f)  => We are enforcing a rule here when it comes to changing damage.
         {
            damage = amount;
         }
       }
     private:
       float damage;
    };



We can define like this  

class Character{
   public: // Section public
   Vector2 getworldPos() // Create getworldPos
    {                    
      return worldPos;   // Return vector2 worldPos
    }

    or
 we can write in a more compact form

Vector2 getWorldPos()  {return worldPos}
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