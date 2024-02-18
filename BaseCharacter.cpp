#include "BaseCharacter.h"


BaseCharacter::BaseCharacter() // Use scope resolution operator to derive the constructor class from the "BaseCharacter.h"
{
    
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame; // Assign worldpos to worldPosLastFrame
}

Rectangle BaseCharacter::GetCollisionRec()
{
  return Rectangle
  {
    screenPos.x,
    screenPos.y,
    width * scale,
    height * scale
  };
}