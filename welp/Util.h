// Author(s): Chris, Johnny

#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

int convertStringToInt(string input);
inline bool isInteger(const string & s);
string getUserInputAsString();
int getUserInputAsInt();
int getUserInputAsInt(int min, int max);
int getUserInputAsInt(int min, size_t max);
void clearScreen();
void pause();
