// Author(s): Chris, Johnny

#include <string>
#include <iostream>
#include <stdlib.h>


int convertStringToInt(std::string input);
inline bool isInteger(const std::string & s);
std::string getUserInputAsString();
int getUserInputAsInt();
int getUserInputAsInt(int min, int max);
int getUserInputAsInt(int min, size_t max);
void clearScreen();
void pause();
