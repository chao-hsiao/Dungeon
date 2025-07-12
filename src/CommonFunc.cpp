#include "CommonFunc.h"

int getUserChoice(const string &prompt, int minChoice, int maxChoice)
{
    int choice;
    while (true)
    {
        cout << ">> " << prompt << ": ";
        cin >> choice;
        cout << endl;
        if (cin.fail() || choice < minChoice || choice > maxChoice)
        {
            cin.clear();            // Clears the error flags
            cin.ignore(1000, '\n'); // Ignore the incorrect input till the newline or 1000 characters
            cout << "Invalid choice! Please choose again." << endl;
            continue;
        }
        break; // Break the loop if the choice is valid
    }
    return choice;
}