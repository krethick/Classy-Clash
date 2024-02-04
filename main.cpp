/*
   Animating the Character:
       * Change Direction
       * Animate the knight
       * Multiple sprite sheets
         i) Idle
         ii) Run

   // Ternary operator (This operator works on three arguments only in C++)
    direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;  

    direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; 
                This is equivalent to
    if(direction.x<0.f) // If Direction is less than 0
           {
             rightLeft = -1.f; // Face towards the left i.e the negative direction
           }
           else
           {
            rightLeft = 1.f; // Face towards the right i.e the positive direction
           }

*/


#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
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