#include "TextColour.h"
#include <iostream>

void SetColour(int textColor)
{
    std::cout << "\033[" << textColor << "m";
}
void ResetColour()
{ 
    std::cout << "\033[0m"; 
}