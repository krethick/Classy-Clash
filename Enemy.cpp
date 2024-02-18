#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) 
{ // ThE Enemy class inherits these variables from the base character.h (note check the Enemy.h)
  worldPos = pos;
  texture = idle_texture;
  idle = idle_texture;
  run = run_texture;
   
  width = texture.width/maxFrames;
  height = texture.height;
}

void Enemy::tick(float deltaTime)
{
   worldPosLastFrame = worldPos;

    // Update animation frame
  // Note we can use a delta time or the GetFrameTime (Both are same)
  runningTime += deltaTime;
  if (runningTime >= updateTime)
  {
    frame++;
    runningTime = 0.f;
    if (frame > maxFrames)
      frame = 0;
  }

  // Draw the knight character (Click shift + alt + f to reform the document )
  Rectangle source{frame * width, 0.f, rightLeft * width, height}; // We use 0.f for x and y
  Rectangle destination{screenPos.x, screenPos.y, scale * width, scale * height};      // We use 4.0 to scale the knight image size
  Vector2 origin{};
  DrawTexturePro(texture, source, destination, origin, 0.f, WHITE);
}

