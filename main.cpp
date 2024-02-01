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

    In Ray Lib a position can be represented by a 2D Vector

    We want to move the character in the direction represented by this vector called MOVE. 
    How do we figure out this characters new position?

    => Vector Addition i.e pos + move = newPos

    The new vector x would be equal to paused x plus moved x and y is calculated similarly
      => x = pos.x + move.x
      => y = pos.y + move.y

   If we want to subtract two vectors:
     A - B = C
     A + (-B) = C

    Vector Operations 
      => There are different vector operations and ray lib contains a math library called raymath which can be 
         used as "raymath.h"
      => Some functions in this library include vector to add, which takes two vectors and adds them together.

           Vector2Add(Vector2 vec1, Vector2 vec2)
           Vector2Subtract(Vector2 vec1, Vector2 vec2)
           Vector2Normalize(Vector2 vec)
           Vector2Scale(Vector2 vec1, float scale)

      Vector2Normalize(Vector2 vec)
        * It takes a vector of a particular length, and it returns a vector pointing in the same direction with
          a length of one. Eg: 1.414 => 1 .

      Vector2Scale(Vector2 vec1, float scale)
        * It takes a vector of a particular size and scales it by the float passed in as the second parameter

    Please refer to Tiled map tutorial.pdf to get more info on Vectors
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