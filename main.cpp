/*
   Classes :
     * User defined type
     * Contain thier own variables - Data Members (member variables)
     * Own methods / functions- Methods(Member functions)
     * Declared with the class keyword
    
    Note: Data members and methods are both considered members of the class

    Eg:                        
    class Goblin
    {

    };

    Goblin gobby;

    Eg: For a structure
    struct Goblin
    {
       
    };

    Goblin gobby;

    As both are looking similar so what's the difference between a class and a struct ?
     => The difference is in the access levels.

    The body of a class is private by default, that means its member variables and functions are inaccessible outside the class.
    Wheras a struct has a public body by default, so its member variables and functions are accessible from outside.

    Eg:

     struct Rectangle
     {
        float x;
        float y;
        float width;
        float height;
     };

     Rectangle rec{};
     rec.y = 20.f // Accessible because structure by default is public

       For a Class
     class Barbarian
     {
        float damamge;  => private
     };

     // When we create an instance of this class and then attempt to access this private variable directly and change it we
        get an error (Error: inaccessible) because this float variable is inaccessible, it's private(conan.damage = 200.f)
     Barbarian conan {};
     conan.damage = 200.f

    Why we keep things Private ?
        * Making inner workings of a class private hides the details of theat class and its implementation from the user, thus
          protecting the user from potentially messing things up.
        *  Also helps in maintainability of classes.
        *  Loose Coupling (classes are mostly independent) 
        * Encapsulation:
            When the state of a class or the current values of its variable is hidden from the outside of the class 
            Wrapping of data into a single unit.
    
     What is abstraction :-
        The act of representing essential data without including background details

    A class can have multiple sections, each with thier own access levels, and we achieve this by the use of the access modifiers.

        class Car
    public: => Access modifiers (public section)
      void brake(); 
    private: => Access modifiers (private section)
      float brakeFluid;
      float speed;
      int ABSValves;

      // Create an instance of the car class
      Car buick;
      // Right now if we attempt to access the private variables and change them directly, we'd get an error.
      buick.brakeFluid -= 2.5f;
      buick.speed -= 10.f;

      // Instead if we call the public function, which takes care of the manipulation of those variables itself, then we eliminate the risk
      // of breaking incorrectly and messing up the calculations for these variables.
      // This function here provides us with a public interface for the user of the class.
      buick.brake();
        
*/ 


#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs

// Create a class character
class Character{
  public: // Section public

  private: // Section Private
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