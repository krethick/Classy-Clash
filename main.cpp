/*
   Movement
      Now say we have a map and the upper left corner of that map is at the World Origin, which has
      X and Y coordinates of 0.

       if(IsKeyDown(KEY_A)) direction.x -= 1.0; // Moves to the left so negative
        // if you have a single statement in if else then we don't require {}.

        mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
          -> We are subtracting this quantity(Vector2Scale(Vector2Normalize(direction), speed)) from map pos and this quantity(Vector2Scale(Vector2Normalize(direction), speed)) is the result
             of scaling the normalized direction vector by speed.
*/


#include "raylib.h"
#include "raymath.h" // Header file to solve vector related programs
int main()
{
    int windowDimensions[2];
    windowDimensions [0] = 384;
    windowDimensions [1] = 384;

    // Initialise this window and use it before loop
    InitWindow(windowDimensions[0],windowDimensions[1], "Classy-Clash");

    Texture2D nature_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0}; // This is for the map position 
    float speed {4.0};
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
           
        }
        
        DrawTextureEx(nature_map, mapPos, 0.0, 4.0, WHITE); // We are drawing the map into the screen

        EndDrawing();
    }
    UnloadTexture(nature_map);
    CloseWindow();
}