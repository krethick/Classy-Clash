/*
  In Prop.h

  class Prop
  {
    public:
       Prop(Vector2 pos);
    
    private:
      Texture2D texture{};
      Vector2 worldPos{};
      float scale;
  }

  Prop.cpp
  Prop::Prop(Vector2 pos)
  {
    worldPos = pos; X // But this is actually not the most effecient way to do it because world pos is already initialised in Prop.h
  }

  // How to solve this extra assignment step ?
    => We can do that by the use of memeber initializer lists
    => We create like this 
        Prop::Prop(Vector2 pos) : 
          worldPos(pos)

    Now what if the constructor has more than one input parameter?
     Let me say there is a second paramter called Texture2D tex

      In Prop.h
  
  class Prop
  {
    public:
       Prop(Vector2 pos, Texture2D tex);
    
    private:
      Texture2D texture{};
      Vector2 worldPos{};
      float scale;
  }

  Prop.cpp
  Prop::Prop(Vector2 pos) : 
        worldPos(pos),
        texture(tex) 
  {

  }

       
*/

#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
   worldPos(pos),
   texture(tex)
{

}