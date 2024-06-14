#include <stdlib.h>
#include <iostream>

#include "utils.cpp"

using namespace std;

int main()
{
    string filename = "items.csv";
    openFile(filename);

    cout << "=============================================================" << endl;
    cout << "**********=   WELCOME TO ITEM MANAGEMENT SYSTEM     =********" << endl;
    cout << "**********=   Developed by Precieux Mugisha - RCA   =********" << endl;
    cout << "=============================================================" << endl;

    cout << "The commands available are: itemslist, itemadd and help\n"
         << "Use help to view command usage" << endl;

    string input;
    while (true)
    {
        cout << ">> ";
        if (!getline(cin, input))
        {
            break; // Exit if there's no more input
        }
        processCommand(input);
    }

    return 0;
}