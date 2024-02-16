/*
  How do we get around especially the errors including same header file twice ? 
   => Conditional Compilation:
         
*/

// This preprocessor directive checks whether a specific identifier/header file is defined or not
// If the identifier is not defined, the code within the #ifndef block is processed. 
// If the identifier is defined, the code within the #ifndef block is skipped.

#ifndef BASE_CHARACTER_H  // if not defined, the header checks if BASE_CHARACTER_H exists (Yes it don't exist)
                          // if already exists the line of code does'nt execute.
                         
#define BASE_CHARACTER_H // If true define BASE_CHARACTER_H

class BaseCharacter  // Create the base the BaseCharacter
{
    public:
       BaseCharacter();
    private:
};


#endif // Exit.