#include <iostream>
#include <cmath>
#include <limits>

// Student name: Tomas Vosylius / 1042957

using namespace std;

bool IntegerMeetsBaseRequirements(int base)
{
    // Base number has be one of (2, 8, 10, or 16).
    // This will check whether number is power of 2 or not.
    // It'll also check
    //      if number isn't 4
    //      if number is 10
    //      if it is in range [2, 16]
    return (( !((base) & (base - 1)) || base == 10) && base >= 2 && base <= 16 && base != 4);
}
bool InputMeetsStringRequirements(string input)
{
    return (input.length() == 4);
}
void Calculate(char input[4], int inputBase, int outputBase)
{
    int
        digit = 0,
        sum = 0;
    for(int c = 0; c < 4; c++)
    {
        digit = (input[c] >= 'A' ? input[c] - 55 : input[c] - '0'); // A - F has to be 10..15, not 65..70
        sum += digit * pow(outputBase, 4 - (c+1)); // As we go further on loop, power goes down (if c=3, power will be 4-(c+1), so ^(4-(3+1))=^1
    }
    std::cout << "Output of \"" << input << "\" (base " << inputBase << "): " << sum << " (base " << outputBase << ")" << std::endl;
}

int main()
{
    char consoleCommand = 'C';
    do
    {
        int
            inputBase = -1,
            outputBase = -1;
        string
            input;

        // -----------------------------------------------------------------------------------
        // Input-base
        do
        {
            std::cout << "Enter input base:" << std::endl;
            std::cin >> inputBase;

            // Ignoring character or string inputs, otherwise it'll give us infinite loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        }
        while(!IntegerMeetsBaseRequirements(inputBase));

        // -----------------------------------------------------------------------------------
        // Output-base
        do
        {
            std::cout << "Enter output base:" << std::endl;
            std::cin >> outputBase;

            // Ignoring character or string inputs, otherwise it'll give us infinite loop
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        }
        while(!IntegerMeetsBaseRequirements(outputBase));

        std::cout << "Input base: " << inputBase << ", output base: " << outputBase << std::endl;

        // -----------------------------------------------------------------------------------
        // Input
        do
        {
            // input is string now, since user can input string of any length, but char array is size of only 4. This could cause crash.
            // We will later convert 'string input' to 'char chars[4]' using std::copy
            std::cout << "Enter your input (in base of " << inputBase << ")" << std::endl;
            std::cin >> input;
        }
        while(!InputMeetsStringRequirements(input));

        // -----------------------------------------------------------------------------------
        // Converting string to fixed-size char array
        char
            chars[5]; // Last index of array has to be End Of Line character ('\0')
        std::copy(input.begin(), input.end(), chars);
        chars[4] = '\0';

        // -----------------------------------------------------------------------------------
        // Checking if the input meets selected input-base.
        // For example we can't input CAFE if we selected 2,8 or 10 as input-base. It's only available when selected input-base is 16.
        for(int c = 0; c < 4; c++)
        {
            if((chars[c] > '1' && inputBase == 2) ||
               (chars[c] > '7' && inputBase == 8) ||
               (chars[c] > '9' && inputBase == 10) ||
               (!((chars[c] >= 'A' && chars[c] <= 'F') || (chars[c] <= '9')) && inputBase == 16)
               || chars[c] < '0')
            {


                std::cout << "Input doesn't meet your selected input-base ("<< inputBase <<")! (At index [" << c << "]:" << int(chars[c]) << ")" << std::endl;
                return 0;
            }
        }

        Calculate(chars, inputBase, outputBase);
        std::cout << "Type C and press ENTER to repeat. Anything else will exit the program: ";
        std::cin >> consoleCommand;
        std::cout << std::endl;
    }
    while(consoleCommand == 'C');
    return 0;
}

