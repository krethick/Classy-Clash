/*
   Drawing the Character:
        * We are going to use DrawTexturePro()
        * DrawTexturePro() allows us to Scale the Character
        * Helps us use the Sprite Sheet.
        
    DrawTexturePro(texture,source,dest,origin,rotation,tint); : 
         It takes a few parameters
                * texture is the sprite sheet
                * source is a section in the sprite sheet
                * dest is a destination rectangle
                * origin is the origin(the point from which something starts) of the texture
                * rotaion is rotaion
                * tint is a color
    
    * Right now we are using a sprite sheet now. Eg(Sprite image has 5 images on it)
    * Source is going to dictate which part of the spreadsheet we're going to use
    * Incase if we want the second animation frame from the sheet, then this rectangle represents the source.
       -> It is an X, which is the local positon on the sprite sheet
       -> So in this case, it's going to be this distance here that we're moving to the right.
       -> It has a Y, which in this case is going to be 0.
       -> Width is going to be width of the sprite sheet i.e w/6
       -> Since we have six animation frames and height is going to be height of the sprite sheet.
    
    Origin is simply a Vector2 local to the rectangle

   Important point :
     * If we use a literal number with decimal values, 4.0 the compiler considers
       this to be double.
    * If we place f at the end of any number like 4.0f that value changes to float.

  knight.width In order to convert this to float we can use like this (float)knight.width
     -> It takes the value to the right and convets it to a float.
     -> It is called as a C type cast (type casting) it comes from C programming language.
   
   For more info on type casting refer this https://www.scaler.com/topics/type-casting-in-c/

 
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

         // Draw the knight character
        Rectangle source{0.f,0.f, (float)knight.width/6.f, (float)knight.height}; // We use 0.f for x and y
        Rectangle destination {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height}; // We use 4.0 to scale the knight image size
        Vector2 origin{};
        DrawTexturePro(knight,source,destination,origin,0.f,WHITE);
        EndDrawing();
    }
    UnloadTexture(nature_map);
    CloseWindow();
}