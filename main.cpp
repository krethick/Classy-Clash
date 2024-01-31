/*
  Top Down Game Setup
     void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
    
*/


#include "raylib.h"
int main()
{
    int windowDimensions[2];
    windowDimensions [0] = 384;
    windowDimensions [1] = 384;

    // Initialise this window and use it before loop
    InitWindow(windowDimensions[0],windowDimensions[1], "Classy-Clash");

    Texture2D nature_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        Vector2 mapPos{0.0, 0.0}; // This is for the map position 
        DrawTextureEx(nature_map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(nature_map);
    CloseWindow();
}