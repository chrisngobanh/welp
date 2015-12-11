#include "Util.h"

// Handler Functions (Reusable Code)

/**
 * Pause Program
 * Author(s): Kevin, Chris
 *
 * A cross-platform method of pausing the program
 * Windows uses system("PAUSE")
 * All other platforms use the 'read' bash command to simulate system("PAUSE")
 */
#ifdef _WIN32
void pauseProgram()
{
    system("PAUSE");
}
#else
void pauseProgram()
{
    system( "read -n 1 -s -p \"Press any key to continue . . . \"" );
}
#endif
/**
 * Is Integer Handler
 * Author(s): Johnny
 *
 * This function takes a string and checks if it can be converted to an int
 * Returns true if the string can be an int, and false if the string cannot be an int
 */
inline bool isInteger(const string & s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}


/**
 * Covert String To Int Handler
 * Author(s): Chris
 *
 * This function converts a string to an int
 * If the string is not an int, then it returns -1
 * Otherwise, it'll return an int that is the string's int form
 */
int convertStringToInt(string input)
{
    if (!isInteger(input)) return -1;
    return atoi(input.c_str());
}

/**
 * Get User Input Handler (String)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * It returns the user input as string.
 * Ignores empty lines
 */
string getUserInputAsString()
{
    string input;
    // Check if user input is empty. If it isn't, then end loop
    while (getline(cin, input))
    {
        if (input.size()) break;
    }
    return input;
}

/**
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt()
{
    while (true) {
        string input = getUserInputAsString();
        int intInput = convertStringToInt(input);

        if (intInput == -1)
        {
            cout << "Invalid Input. Try again: ";
        }
        else
        {
            return intInput;
        }
    }
}

/**
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * First parameter (int) is the min value that the input can be
 * Second parameter (int) is the max value that the input can be
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt(int min, int max)
{
    while (true) {
        int intInput = getUserInputAsInt();

        if (intInput < min || intInput > max)
        {
            cout << "Invalid Input. Try again: ";
        }
        else
        {
            return intInput;
        }
    }
}

/**
 * Get User Input Handler (Int)
 * Author(s): Chris
 *
 * This function gets user input when called.
 * First parameter (int) is the min value that the input can be
 * Second parameter (size_t) is the max value that the input can be
 * It returns the user input as int.
 * Ignores empty lines and bad input
 */
int getUserInputAsInt(int min, size_t max)
{
    return getUserInputAsInt(min, (int)max);
}

/**
 * Clear Screen Handler
 * Author(s): Chris
 *
 * This function clears the screen by making a lot of empty new lines
 * This method is cross platform
 */
#ifdef _WIN32
void clearScreen()
{
    system("CLS");
}

#else

void clearScreen()
{
    cout << string( 100, '\n' );
}

#endif
