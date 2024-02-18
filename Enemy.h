#include "raylib.h"
#include "BaseCharacter.h"

class Enemy : public BaseCharacter // Enemy functionalities derived from the BaseCharacter class
{
    public:
      Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture); // Define a constructor
      
      virtual void tick(float deltaTime) override; // two or more functions can have the same name but different parameters. 
      

    private:
       

};