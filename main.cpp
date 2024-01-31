/*
   Vectors:
     It can represent a direction and a position in a 2D Space. It can also facilitate movement in a video game.

     A vector is a mathematical quantity with two main properties 
       * Direction
       * Magnitude (length) of a vector
    
    Vectors can be broken down into components:
      * A 2D Vector has an x component and a y component
      * Thats why ray-lib vector two type has an x and a y-variable
      * Together x and the y combine to make a vector.
      * Think of x and y as the distance we have to travel and the x and then the y direction in order 
        to get to the end of the vector.
        
        y----------
        |        * :
        |      *   :                    
        |    *  1  :
        |__*_______: X  


                  * :
           C    *   :
              *  1  : B
            * - - - :
                A

    If we know the values of the X and the y components, how do we get the length off the vector ?
     * Hidden in the diagram 1 here is a right triangle and this is the key to finding that vector length
     * We can find the length of a vector by using the mathematics of right triangles.
     
    Let we have a triangle with sides A and B and C is the side opposite the right angle, also known as the hypotenuse
        
                  * :
           C    *   :
              *   --: B
             *    | :    [] = hypotenues.
            * - - - :
                A

    There is an equation relating these three quantities and it looks like
          
          C2 = A2 + B2.
    
    Let A and B be 1
       * Then C is related to those quantities with this equation
       * 2 = 1^2 + 1^2
       C is roughly equal to 1.414 i.e the sqrt of 2 is 1.414
       * So this is how we can find the length of the vector if we know the x and y components

    Vectors represent a direction, but they can also represent a position in space
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